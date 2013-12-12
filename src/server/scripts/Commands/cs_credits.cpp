/*
* Copyright (C) 2010 - 2013 OpenEmu 5.4.0 <http://www.openemulator.com/>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

/* ScriptData
Name: credits_commandscript
Created by Oracraft
%Complete: 100
Comment: This shows OpenEmu 5.4.0 credits.
EndScriptData */

#include "ScriptPCH.h"
#include "Chat.h"

// **** Script Info ****
class credits_commandscript: public CommandScript
{
public:
    credits_commandscript () :
            CommandScript("credits_commandscript")
    {
    }

    static bool HandleCreditsCommand (ChatHandler* handler, const char* /*args*/)
    {
        handler->PSendSysMessage("");
        handler->PSendSysMessage("__[OpenEmu 5.4.0 Credits]______________________________________________");
        handler->PSendSysMessage("OpenEmulator 5.4.0 : http://www.openemulator.com/");
        handler->PSendSysMessage("");
        handler->PSendSysMessage("This command lists the people, projects, and urls");
        handler->PSendSysMessage("that we would like to thank for their contribution to our project, ");
        handler->PSendSysMessage("whether their influence was direct or indirect.");
        handler->PSendSysMessage("");
        handler->PSendSysMessage("The following people have contributed directly to our project:");
        handler->PSendSysMessage("");
        handler->PSendSysMessage("Kryck, RechTheMoon, BlackPanther, Mario, StupidZed, FrankyRabit,");
        handler->PSendSysMessage("Ramirez, Fraloom, Lasoto, Kronos, Anthodev, Notagain, superllout,");
        handler->PSendSysMessage("Walkum,");
        handler->PSendSysMessage("");
        handler->PSendSysMessage("We would also like to thank the following Sites/Communities:");
        handler->PSendSysMessage("ProjectSkyfire: http://www.projectskyfire.org");
        handler->PSendSysMessage("TrinityCore: http://www.trinitycore.org");
        handler->PSendSysMessage("Mangos: http://www.getmangos.com");
        handler->PSendSysMessage("");
        handler->PSendSysMessage("__[OpenEmu 5.4.0 Credits]______________________________________________");
        return true;
    }

    ChatCommand* GetCommands () const
    {
        static ChatCommand CreditsCommandTable[] =
        {
        { "credits", SEC_PLAYER, true, &HandleCreditsCommand, "", NULL },
        { NULL, 0, false, NULL, "", NULL } };
        return CreditsCommandTable;
    }
};

void AddSC_credits_commandscript ()
{
    new credits_commandscript();
}

