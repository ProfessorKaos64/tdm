/*****************************************************************************
                    The Dark Mod GPL Source Code
 
 This file is part of the The Dark Mod Source Code, originally based 
 on the Doom 3 GPL Source Code as published in 2011.
 
 The Dark Mod Source Code is free software: you can redistribute it 
 and/or modify it under the terms of the GNU General Public License as 
 published by the Free Software Foundation, either version 3 of the License, 
 or (at your option) any later version. For details, see LICENSE.TXT.
 
 Project: The Dark Mod (http://www.thedarkmod.com/)
 
 $Revision: 5800 $ (Revision of last commit) 
 $Date: 2013-06-02 02:49:25 +0200 (Sun, 02 Jun 2013) $ (Date of last commit)
 $Author: grayman $ (Author of last commit)
 
******************************************************************************/

#include "precompiled_game.h"
#pragma hdrstop

static bool versioned = RegisterVersionedFile("$Id: RepeatedBarkTask.cpp 5800 2013-06-02 00:49:25Z grayman $");

#include "RepeatedBarkTask.h"
#include "../Memory.h"
#include "../Library.h"

namespace ai
{

// Default constructor
RepeatedBarkTask::RepeatedBarkTask() :
	CommunicationTask(""),
	_barkRepeatIntervalMin(0), 
	_barkRepeatIntervalMax(0)
{}

RepeatedBarkTask::RepeatedBarkTask(const idStr& soundName, 
		int barkRepeatIntervalMin, int barkRepeatIntervalMax, 
		const CommMessagePtr& message) : 
	CommunicationTask(soundName),
	_barkRepeatIntervalMin(barkRepeatIntervalMin), 
	_barkRepeatIntervalMax(barkRepeatIntervalMax),
	_message(message)
{}

// Get the name of this task
const idStr& RepeatedBarkTask::GetName() const
{
	static idStr _name(TASK_REPEATED_BARK);
	return _name;
}

void RepeatedBarkTask::Init(idAI* owner, Subsystem& subsystem)
{
	// Init the base class
	CommunicationTask::Init(owner, subsystem);

	// Initialise it to play the sound now
	_nextBarkTime = gameLocal.time;
	// greebo: Add some random offset of up to <intervalMax> seconds before barking the first time
	// This prevents guards barking in choirs.
	_nextBarkTime += static_cast<int>(gameLocal.random.RandomFloat()*_barkRepeatIntervalMax);

	// grayman #3182 - previous bark has finished
	_prevBarkDone = true;
}

bool RepeatedBarkTask::Perform(Subsystem& subsystem)
{
	DM_LOG(LC_AI, LT_INFO)LOGSTRING("RepeatedBarkTask performing.\r");

	idAI* owner = _owner.GetEntity();

	// This task may not be performed with empty entity pointers
	assert(owner != NULL);

	// grayman #3182 - when the bark itself is finished, allow idle animations again
	// Use _prevBarkDone to keep from setting playIdleAnimations over and over and over.
	if ( !_prevBarkDone && !IsBarking() )
	{
		owner->GetMind()->GetMemory().currentlyBarking = false;
		_priority = -1; // reset priority
		_prevBarkDone = true;
	}

	if (gameLocal.time >= _nextBarkTime)
	{
		// The time has come, bark now

		// grayman #2169 - no barks while underwater

		// grayman #3182 - no idle barks while performing an idle animation.
		// An idle animation that includes a voice frame command will have set
		// the wait state to 'idle'. An idle animation that has no voice frame
		// command will have set the wait state to 'idle_no_voice'.

		if ( !owner->MouthIsUnderwater() && ( idStr(owner->WaitState()) != "idle" ) )
		{
			int msgTag = 0; // grayman #3355
			// Setup the message to be propagated, if we have one
			if (_message != NULL)
			{
				msgTag = gameLocal.GetNextMessageTag(); // grayman #3355
				owner->AddMessage(_message,msgTag);
			}

			owner->GetMind()->GetMemory().currentlyBarking = true; // grayman #3182 - idle anims cannot start
																   // until this bark is finished
			_prevBarkDone = false; // grayman #3182
			_barkLength = owner->PlayAndLipSync(_soundName, "talk1", msgTag);
		}
		else
		{
			_barkLength = 0;
		}

		_barkStartTime = gameLocal.time;

		// Reset the timer
		if (_barkRepeatIntervalMax > 0)
		{
			_nextBarkTime = static_cast<int>(_barkStartTime + _barkLength + _barkRepeatIntervalMin + 
				gameLocal.random.RandomFloat() * (_barkRepeatIntervalMax - _barkRepeatIntervalMin));
		}
		else
		{
			_nextBarkTime = _barkStartTime + _barkLength + _barkRepeatIntervalMin;
		}
	}

	return false; // not finished yet
}

// Save/Restore methods
void RepeatedBarkTask::Save(idSaveGame* savefile) const
{
	CommunicationTask::Save(savefile);

	savefile->WriteInt(_barkRepeatIntervalMin);
	savefile->WriteInt(_barkRepeatIntervalMax);
	savefile->WriteInt(_nextBarkTime);
	savefile->WriteBool(_prevBarkDone); // grayman #3182

	savefile->WriteBool(_message != NULL);
	if (_message != NULL)
	{
		_message->Save(savefile);
	}
}

void RepeatedBarkTask::Restore(idRestoreGame* savefile)
{
	CommunicationTask::Restore(savefile);

	savefile->ReadInt(_barkRepeatIntervalMin);
	savefile->ReadInt(_barkRepeatIntervalMax);
	savefile->ReadInt(_nextBarkTime);
	savefile->ReadBool(_prevBarkDone); // grayman #3182

	bool hasMessage;
	savefile->ReadBool(hasMessage);
	if (hasMessage)
	{
		_message = CommMessagePtr(new CommMessage);
		_message->Restore(savefile);
	}
	else
	{
		_message = CommMessagePtr();
	}
}

RepeatedBarkTaskPtr RepeatedBarkTask::CreateInstance()
{
	return RepeatedBarkTaskPtr(new RepeatedBarkTask);
}

// Register this task with the TaskLibrary
TaskLibrary::Registrar repeatedBarkTaskRegistrar(
	TASK_REPEATED_BARK, // Task Name
	TaskLibrary::CreateInstanceFunc(&RepeatedBarkTask::CreateInstance) // Instance creation callback
);

} // namespace ai
