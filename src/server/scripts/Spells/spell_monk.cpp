/* Copyright (C) 2010-2013 OpenEmulator <http://www.openemulator.com/>
*
* This file is free software; as a special exception the author gives
* unlimited permission to copy and/or distribute it, with or without
* modifications, as long as this notice is preserved.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum MonkSpells
{
    SPELL_MONK_EXPEL_HARM                       = 115072,
    SPELL_MONK_FISTS_OF_FURY                    = 113656,
    SPELL_MONK_FLYING_SERPENT_KICK              = 101545,
    SPELL_MONK_SPINNING_CRANE_KICK              = 101546,
    SPELL_MONK_TOUCH_OF_DEATH                   = 115080,
    SPELL_MONK_INVOKE_XUEN                      = 123904,
};


