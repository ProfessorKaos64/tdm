/*****************************************************************************
                    The Dark Mod GPL Source Code
 
 This file is part of the The Dark Mod Source Code, originally based 
 on the Doom 3 GPL Source Code as published in 2011.
 
 The Dark Mod Source Code is free software: you can redistribute it 
 and/or modify it under the terms of the GNU General Public License as 
 published by the Free Software Foundation, either version 3 of the License, 
 or (at your option) any later version. For details, see LICENSE.TXT.
 
 Project: The Dark Mod (http://www.thedarkmod.com/)
 
 $Revision: 5166 $ (Revision of last commit) 
 $Date: 2012-01-06 20:35:53 +0200 (Fri, 06 Jan 2012) $ (Date of last commit)
 $Author: greebo $ (Author of last commit)
 
******************************************************************************/

#ifndef TDM_CAMPAIGN_STATISTICS_H
#define TDM_CAMPAIGN_STATISTICS_H

#include "precompiled_game.h"

#include "MissionStatistics.h"

/**
 * Multiple mission stats structs combined => campaign stats.
 * First mission is carrying index 0.
 */
class CampaignStats
{
private:
	// The internal array of statistics
	idList<MissionStatistics> _stats;

public:
	// greebo: Use this operator to get access to the stats of the mission with the given index
	// The internal list will automatically be resized to fit.
	MissionStatistics& operator[] (int index)
	{
		EnsureSize(index + 1);
		return _stats[index];
	}

	const MissionStatistics& operator[] (int index) const
	{
		return _stats[index];
	}

	int Num() const
	{
		return _stats.Num();
	}

	void Save(idSaveGame* savefile) const;
	void Restore(idRestoreGame* savefile);

private:
	void EnsureSize(int size);
};

#endif
