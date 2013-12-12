# Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  Events/childrens_week.cpp
  Events/darkmoon_fair.cpp
  Events/brewfest.cpp
  Events/day_of_the_dead.cpp
  Events/feast_of_winter_veil.cpp
  Events/fireworks_spectacular.cpp
  Events/hallows_end.cpp
  Events/harvest_festival.cpp
  Events/love_is_in_the_air.cpp
  Events/lunar_festival.cpp
  Events/midsummer_fire_festival.cpp
  Events/noblegarden.cpp
  Events/pilgrims_bounty.cpp
  Events/pirates_day.cpp
  Events/wows_anniv.cpp
)

message("  -> Prepared: Events")
