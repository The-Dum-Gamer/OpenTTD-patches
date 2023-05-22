/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file settings_type.h Types related to global configuration settings. */

#ifndef SETTINGS_TYPE_H
#define SETTINGS_TYPE_H

#include "date_type.h"
#include "economy_type.h"
#include "town_type.h"
#include "transport_type.h"
#include "network/network_type.h"
#include "company_type.h"
#include "cargotype.h"
#include "linkgraph/linkgraph_type.h"
#include "zoom_type.h"
#include "openttd.h"
#include "rail_gui_type.h"
#include "station_type.h"
#include "signal_type.h"

/* Used to validate sizes of "max" value in settings. */
const size_t MAX_SLE_UINT8 = UINT8_MAX;
const size_t MAX_SLE_UINT16 = UINT16_MAX;
const size_t MAX_SLE_UINT32 = UINT32_MAX;
const size_t MAX_SLE_UINT = UINT_MAX;
const size_t MAX_SLE_INT8 = INT8_MAX;
const size_t MAX_SLE_INT16 = INT16_MAX;
const size_t MAX_SLE_INT32 = INT32_MAX;
const size_t MAX_SLE_INT = INT_MAX;

/** Settings profiles and highscore tables. */
enum SettingsProfile {
	SP_BEGIN = 0,
	SP_EASY = SP_BEGIN,                       ///< Easy difficulty.
	SP_MEDIUM,                                ///< Medium difficulty.
	SP_HARD,                                  ///< Hard difficulty.

	SP_END,                                   ///< End of setting profiles.

	SP_CUSTOM = SP_END,                       ///< No profile, special "custom" highscore.
	SP_SAVED_HIGHSCORE_END,                   ///< End of saved highscore tables.

	SP_MULTIPLAYER = SP_SAVED_HIGHSCORE_END,  ///< Special "multiplayer" highscore. Not saved, always specific to the current game.
	SP_HIGHSCORE_END,                         ///< End of highscore tables.
};

/** Available industry map generation densities. */
enum IndustryDensity {
	ID_FUND_ONLY, ///< The game does not build industries.
	ID_MINIMAL,   ///< Start with just the industries that must be present.
	ID_VERY_LOW,  ///< Very few industries at game start.
	ID_LOW,       ///< Few industries at game start.
	ID_NORMAL,    ///< Normal amount of industries at game start.
	ID_HIGH,      ///< Many industries at game start.

	ID_CUSTOM,    ///< Custom number of industries.

	ID_END,       ///< Number of industry density settings.
};

/** Possible values for "userelayservice" setting. */
enum UseRelayService {
	URS_NEVER = 0,
	URS_ASK,
	URS_ALLOW,
};

/** Settings related to the difficulty of the game */
struct DifficultySettings {
	byte   competitor_start_time;            ///< Unused value, used to load old savegames.
	byte   competitor_intelligence;          ///< Unused value, used to load old savegames.

	byte   max_no_competitors;               ///< the number of competitors (AIs)
	byte   number_towns;                     ///< the amount of towns
	byte   industry_density;                 ///< The industry density. @see IndustryDensity
	uint32 max_loan;                         ///< the maximum initial loan
	byte   initial_interest;                 ///< amount of interest (to pay over the loan)
	byte   vehicle_costs;                    ///< amount of money spent on vehicle running cost
	uint8  vehicle_costs_in_depot;           ///< amount of money spent on vehicle running cost when in depot
	uint8  vehicle_costs_when_stopped;       ///< amount of money spent on vehicle running cost when vehicle is stopped
	byte   competitor_speed;                 ///< the speed at which the AI builds
	byte   vehicle_breakdowns;               ///< likelihood of vehicles breaking down
	byte   subsidy_multiplier;               ///< payment multiplier for subsidized deliveries
	uint16 subsidy_duration;                 ///< duration of subsidies
	byte   construction_cost;                ///< how expensive is building
	byte   terrain_type;                     ///< the mountainousness of the landscape
	byte   quantity_sea_lakes;               ///< the amount of seas/lakes
	bool   economy;                          ///< how volatile is the economy
	bool   line_reverse_mode;                ///< reversing at stations or not
	bool   disasters;                        ///< are disasters enabled
	byte   town_council_tolerance;           ///< minimum required town ratings to be allowed to demolish stuff
	bool   money_cheat_in_multiplayer;       ///< is the money cheat permitted for non-admin multiplayer clients
	bool   rename_towns_in_multiplayer;      ///< is renaming towns permitted for non-admin multiplayer clients
	bool   override_town_settings_in_multiplayer; ///< is overriding town settings permitted for non-admin multiplayer clients
};

/** Settings relating to viewport/smallmap scrolling. */
enum ViewportScrollMode {
	VSM_VIEWPORT_RMB_FIXED, ///< Viewport moves with mouse movement on holding right mouse button, cursor position is fixed.
	VSM_MAP_RMB_FIXED,      ///< Map moves with mouse movement on holding right mouse button, cursor position is fixed.
	VSM_MAP_RMB,            ///< Map moves with mouse movement on holding right mouse button, cursor moves.
	VSM_MAP_LMB,            ///< Map moves with mouse movement on holding left mouse button, cursor moves.
	VSM_END,                ///< Number of scroll mode settings.
};

/** Settings related to time display. This may be loaded from the savegame and/or overriden by the client. */
struct TimeSettings {
	bool   time_in_minutes;                  ///< whether to use the hh:mm conversion when printing dates
	uint16 ticks_per_minute;                 ///< how many ticks per minute
	uint16 clock_offset;                     ///< clock offset in minutes
};

/** Settings related to the GUI and other stuff that is not saved in the savegame. */
struct GUISettings : public TimeSettings {
	bool   sg_full_load_any;                 ///< new full load calculation, any cargo must be full read from pre v93 savegames
	bool   lost_vehicle_warn;                ///< if a vehicle can't find its destination, show a warning
	bool   restriction_wait_vehicle_warn;    ///< if a vehicle is waiting for an extended time due to a routing restriction, show a warning
	uint8  order_review_system;              ///< perform order reviews on vehicles
	uint8  no_depot_order_warn;              ///< if a non-air vehicle doesn't have at least one depot order, show a warning
	bool   vehicle_income_warn;              ///< if a vehicle isn't generating income, show a warning
	bool   show_finances;                    ///< show finances at end of year
	bool   sg_new_nonstop;                   ///< ttdpatch compatible nonstop handling read from pre v93 savegames
	bool   new_nonstop;                      ///< ttdpatch compatible nonstop handling
	uint8  stop_location;                    ///< what is the default stop location of trains?
	uint8  auto_scrolling;                   ///< scroll when moving mouse to the edge (see #ViewportAutoscrolling)
	byte   errmsg_duration;                  ///< duration of error message
	uint16 hover_delay_ms;                   ///< time required to activate a hover event, in milliseconds
	bool   link_terraform_toolbar;           ///< display terraform toolbar when displaying rail, road, water and airport toolbars
	uint8  smallmap_land_colour;             ///< colour used for land and heightmap at the smallmap
	uint8  scroll_mode;                      ///< viewport scroll mode
	bool   smooth_scroll;                    ///< smooth scroll viewports
	bool   measure_tooltip;                  ///< show a permanent tooltip when dragging tools
	byte   liveries;                         ///< options for displaying company liveries, 0=none, 1=self, 2=all
	bool   prefer_teamchat;                  ///< choose the chat message target with \<ENTER\>, true=all clients, false=your team
	uint8  advanced_vehicle_list;            ///< use the "advanced" vehicle list
	uint8  loading_indicators;               ///< show loading indicators
	uint8  default_rail_type;                ///< the default rail type for the rail GUI
	uint8  default_road_type;                ///< the default road/tram types for the road/tram GUI
	uint8  toolbar_pos;                      ///< position of toolbars, 0=left, 1=center, 2=right
	uint8  statusbar_pos;                    ///< position of statusbar, 0=left, 1=center, 2=right
	uint8  window_snap_radius;               ///< windows snap at each other if closer than this
	uint8  window_soft_limit;                ///< soft limit of maximum number of non-stickied non-vital windows (0 = no limit)
	ZoomLevel zoom_min;                      ///< minimum zoom out level
	ZoomLevel zoom_max;                      ///< maximum zoom out level
	ZoomLevel sprite_zoom_min;               ///< maximum zoom level at which higher-resolution alternative sprites will be used (if available) instead of scaling a lower resolution sprite
	byte   autosave;                         ///< how often should we do autosaves?
	uint16 autosave_custom_days;             ///< custom autosave interval in days
	uint16 autosave_custom_minutes;          ///< custom autosave interval in real-time minutes
	bool   threaded_saves;                   ///< should we do threaded saves?
	bool   keep_all_autosave;                ///< name the autosave in a different way
	bool   autosave_on_exit;                 ///< save an autosave when you quit the game, but do not ask "Do you really want to quit?"
	bool   autosave_on_network_disconnect;   ///< save an autosave when you get disconnected from a network game with an error?
	uint8  date_format_in_default_names;     ///< should the default savegame/screenshot name use long dates (31th Dec 2008), short dates (31-12-2008) or ISO dates (2008-12-31)
	byte   max_num_autosaves;                ///< controls how many autosavegames are made before the game starts to overwrite (names them 0 to max_num_autosaves - 1)
	uint8  savegame_overwrite_confirm;       ///< Mode for when to warn about overwriting an existing savegame
	bool   population_in_label;              ///< show the population of a town in its label?
	uint8  right_mouse_btn_emulation;        ///< should we emulate right mouse clicking?
	uint8  scrollwheel_scrolling;            ///< scrolling using the scroll wheel?
	uint8  scrollwheel_multiplier;           ///< how much 'wheel' per incoming event from the OS?
	bool   viewport_map_scan_surroundings;   ///< look for the most important tile in surroundings
	bool   show_slopes_on_viewport_map;      ///< use slope orientation to render the ground
	uint32 default_viewport_map_mode;        ///< the mode to use by default when a viewport is in map mode, 0=owner, 1=industry, 2=vegetation
	uint32 action_when_viewport_map_is_dblclicked; ///< what to do when a doubleclick occurs on the viewport map
	uint32 show_scrolling_viewport_on_map;   ///< when a no map viewport is scrolled, its location is marked on the other map viewports
	bool   show_bridges_on_map;              ///< bridges are rendered on a viewport in map mode
	bool   show_tunnels_on_map;              ///< tunnels are rendered on a viewport in map mode
	bool   use_owner_colour_for_tunnelbridge;///< bridges and tunnels are rendered with their owner's colour
	bool   timetable_arrival_departure;      ///< show arrivals and departures in vehicle timetables
	uint8  max_departures;                   ///< maximum number of departures to show per station
	uint16 max_departure_time;               ///< maximum time in advance to show departures
	uint16 departure_calc_frequency;         ///< how often to calculate departures (in ticks)
	bool   departure_show_vehicle;           ///< whether to show vehicle names with departures
	bool   departure_show_group;             ///< whether to show group names with departures
	bool   departure_show_company;           ///< whether to show company names with departures
	bool   departure_show_vehicle_type;      ///< whether to show vehicle type icons with departures
	bool   departure_show_vehicle_color;     ///< whether to show vehicle type icons in silver instead of orange
	bool   departure_larger_font;            ///< whether to show the calling at list in a larger font
	bool   departure_destination_type;       ///< whether to show destination types for ports and airports
	bool   departure_show_both;              ///< whether to show departure and arrival times on the same line
	bool   departure_only_passengers;        ///< whether to only show passenger services
	bool   departure_smart_terminus;         ///< whether to only show passenger services
	uint8  departure_conditionals;           ///< how to handle conditional orders
	bool   departure_show_all_stops;         ///< whether to show stops regardless of loading/unloading done at them
	bool   departure_merge_identical;        ///< whether to merge identical departures
	bool   right_mouse_wnd_close;            ///< close window with right click
	bool   pause_on_newgame;                 ///< whether to start new games paused or not
	SignalGUISettings signal_gui_mode;       ///< select which signal types are shown in the signal GUI
	SignalCycleSettings cycle_signal_types;  ///< Which signal types to cycle with the build signal tool.
	SignalType default_signal_type;          ///< The default signal type, which is set automatically by the last signal used. Not available in Settings.
	Year   coloured_news_year;               ///< when does newspaper become coloured?
	bool   override_time_settings;           ///< Whether to override time display settings stored in savegame.
	bool   timetable_in_ticks;               ///< whether to show the timetable in ticks rather than days
	bool   timetable_leftover_ticks;         ///< whether to show leftover ticks after converting to minutes/days, in the timetable
	bool   timetable_start_text_entry;       ///< whether to enter timetable start times as text (hhmm format)
	uint8  date_with_time;                   ///< whether to show the month and year with the time
	bool   quick_goto;                       ///< Allow quick access to 'goto button' in vehicle orders window
	bool   auto_euro;                        ///< automatically switch to euro in 2002
	byte   drag_signals_density;             ///< many signals density
	bool   drag_signals_fixed_distance;      ///< keep fixed distance between signals when dragging
	Year   semaphore_build_before;           ///< build semaphore signals automatically before this year
	byte   news_message_timeout;             ///< how much longer than the news message "age" should we keep the message in the history
	bool   show_track_reservation;           ///< highlight reserved tracks.
	byte   station_numtracks;                ///< the number of platforms to default on for rail stations
	byte   station_platlength;               ///< the platform length, in tiles, for rail stations
	bool   station_dragdrop;                 ///< whether drag and drop is enabled for stations
	bool   station_show_coverage;            ///< whether to highlight coverage area
	bool   persistent_buildingtools;         ///< keep the building tools active after usage
	uint32 last_newgrf_count;                ///< the numbers of NewGRFs we found during the last scan
	byte   missing_strings_threshold;        ///< the number of missing strings before showing the warning
	uint8  graph_line_thickness;             ///< the thickness of the lines in the various graph guis
	bool   show_train_length_in_details;     ///< show train length in vehicle details window top widget
	bool   show_train_weight_ratios_in_details;   ///< show train weight ratios in vehicle details window top widget
	bool   show_vehicle_group_in_details;    ///< show vehicle group in vehicle details window top widget
	bool   show_restricted_signal_default;   ///< Show restricted electric signals using the default sprite
	bool   show_all_signal_default;          ///< Show all signals using the default sprite
	bool   show_adv_tracerestrict_features;  ///< Show advanced trace restrict features in UI
	bool   show_progsig_ui;                  ///< Show programmable pre-signals feature in UI
	bool   show_noentrysig_ui;               ///< Show no-entry signals feature in UI
	bool   show_veh_list_cargo_filter;       ///< Show cargo list filter in UI
	uint8  osk_activation;                   ///< Mouse gesture to trigger the OSK.
	byte   starting_colour;                  ///< default color scheme for the company to start a new game with
	bool   show_newgrf_name;                 ///< Show the name of the NewGRF in the build vehicle window
	bool   show_cargo_in_vehicle_lists;      ///< Show the cargoes the vehicles can carry in the list windows
	bool   show_wagon_intro_year;            ///< Show the introduction year for wagons in the build vehicle window
	bool   auto_remove_signals;              ///< automatically remove signals when in the way during rail construction
	uint16 refresh_rate;                     ///< How often we refresh the screen (time between draw-ticks).
	uint16 fast_forward_speed_limit;         ///< Game speed to use when fast-forward is enabled.
	uint8  show_vehicle_route_mode;          ///< How to show a vehicle's route when one of its windows is focused
	bool   show_vehicle_route;               ///< Show route lines when vehicles route overlay is being shown
	bool   show_vehicle_route_steps;         ///< Show route step markers when vehicles route overlay is being shown
	uint8  dash_level_of_route_lines;        ///< the dash level passed to GfxDrawLine() (plain if 0)
	bool   show_vehicle_list_company_colour; ///< show the company colour of vehicles which have an owner different to the owner of the vehicle list
	bool   enable_single_veh_shared_order_gui;    ///< enable showing a single vehicle in the shared order GUI window
	bool   show_adv_load_mode_features;      ///< enable advanced loading mode features in UI
	bool   disable_top_veh_list_mass_actions;     ///< disable mass actions buttons for non-group vehicle lists
	bool   adv_sig_bridge_tun_modes;         ///< Enable advanced modes for signals on bridges/tunnels.
	bool   sort_track_types_by_speed;        ///< Sorts track types by compatibility first, and speed next, instead of newGRF slot
	bool   show_depot_sell_gui;              ///< Show go to depot and sell in UI
	bool   open_vehicle_gui_clone_share;     ///< Open vehicle GUI when share-cloning vehicle from depot GUI
	uint8  linkgraph_colours;                ///< linkgraph overlay colours
	uint8  vehicle_names;                    ///< Vehicle naming scheme
	bool   shade_trees_on_slopes;            ///< Shade trees on slopes
	uint8  station_rating_tooltip_mode;      ///< Station rating tooltip mode
	uint8  demolish_confirm_mode;            ///< Demolition confirmation mode
	bool   dual_pane_train_purchase_window;  ///< Dual pane train purchase window
	bool   dual_pane_train_purchase_window_dual_buttons;  ///< Dual pane train purchase window: dual buttons
	bool   allow_hiding_waypoint_labels;     ///< Allow hiding waypoint viewport labels
	uint8  disable_water_animation;          ///< Disable water animation depending on zoom level
	bool   show_order_occupancy_by_default;  ///< Show order occupancy by default in vehicle order window
	bool   show_order_management_button;     ///< Show order management button in vehicle order window
	bool   show_group_hierarchy_name;        ///< Show the full hierarchy in group names
	bool   show_vehicle_group_hierarchy_name;///< Show the full group hierarchy in vehicle names

	uint16 console_backlog_timeout;          ///< the minimum amount of time items should be in the console backlog before they will be removed in ~3 seconds granularity.
	uint16 console_backlog_length;           ///< the minimum amount of items in the console backlog before items will be removed.

	uint8  station_gui_group_order;          ///< the order of grouping cargo entries in the station gui
	uint8  station_gui_sort_by;              ///< sort cargo entries in the station gui by station name or amount
	uint8  station_gui_sort_order;           ///< the sort order of entries in the station gui - ascending or descending
	uint16 network_chat_box_width_pct;       ///< width of the chat box in percent
	uint8  network_chat_box_height;          ///< height of the chat box in lines
	uint16 network_chat_timeout;             ///< timeout of chat messages in seconds

	uint8  developer;                        ///< print non-fatal warnings in console (>= 1), copy debug output to console (== 2)
	bool   show_date_in_logs;                ///< whether to show dates in console logs
	bool   newgrf_developer_tools;           ///< activate NewGRF developer tools and allow modifying NewGRFs in an existing game
	bool   ai_developer_tools;               ///< activate AI/GS developer tools
	bool   scenario_developer;               ///< activate scenario developer: allow modifying NewGRFs in an existing game
	uint8  settings_restriction_mode;        ///< selected restriction mode in adv. settings GUI. @see RestrictionMode
	bool   newgrf_show_old_versions;         ///< whether to show old versions in the NewGRF list
	uint8  newgrf_default_palette;           ///< default palette to use for NewGRFs without action 14 palette information
	bool   console_show_unlisted;            ///< whether to show unlisted console commands
	bool   newgrf_disable_big_gui;           ///< whether to disable "big GUI" NewGRFs

	bool   scale_bevels;                     ///< bevels are scaled with GUI scale.

	/**
	 * Returns true when the user has sufficient privileges to edit newgrfs on a running game
	 * @return whether the user has sufficient privileges to edit newgrfs in an existing game
	 */
	bool UserIsAllowedToChangeNewGRFs() const
	{
		return this->scenario_developer || this->newgrf_developer_tools;
	}
};

/** Settings related to sound effects. */
struct SoundSettings {
	bool   news_ticker;                      ///< Play a ticker sound when a news item is published.
	bool   news_full;                        ///< Play sound effects associated to certain news types.
	bool   new_year;                         ///< Play sound on new year, summarising the performance during the last year.
	bool   confirm;                          ///< Play sound effect on successful constructions or other actions.
	bool   click_beep;                       ///< Beep on a random selection of buttons.
	bool   disaster;                         ///< Play disaster and accident sounds.
	bool   vehicle;                          ///< Play vehicle sound effects.
	bool   ambient;                          ///< Play ambient, industry and town sounds.
};

/** Settings related to music. */
struct MusicSettings {
	byte playlist;     ///< The playlist (number) to play
	byte music_vol;    ///< The requested music volume
	byte effect_vol;   ///< The requested effects volume
	byte custom_1[33]; ///< The order of the first custom playlist
	byte custom_2[33]; ///< The order of the second custom playlist
	bool playing;      ///< Whether music is playing
	bool shuffle;      ///< Whether to shuffle the music
};

/** Settings related to currency/unit systems. */
struct LocaleSettings {
	byte        currency;                         ///< currency we currently use
	byte        units_velocity;                   ///< unit system for velocity of trains and road vehicles
	byte        units_velocity_nautical;          ///< unit system for velocity of ships and aircraft
	byte        units_power;                      ///< unit system for power
	byte        units_weight;                     ///< unit system for weight
	byte        units_volume;                     ///< unit system for volume
	byte        units_force;                      ///< unit system for force
	byte        units_height;                     ///< unit system for height
	std::string digit_group_separator;            ///< thousand separator for non-currencies
	std::string digit_group_separator_currency;   ///< thousand separator for currencies
	std::string digit_decimal_separator;          ///< decimal separator
};

/** Settings related to news */
struct NewsSettings {
	uint8 arrival_player;                                 ///< NewsDisplay of vehicles arriving at new stations of current player
	uint8 arrival_other;                                  ///< NewsDisplay of vehicles arriving at new stations of other players
	uint8 accident;                                       ///< NewsDisplay of accidents that occur
	uint8 accident_other;                                 ///< NewsDisplay if a vehicle from another company is involved in an accident
	uint8 company_info;                                   ///< NewsDisplay of general company information
	uint8 open;                                           ///< NewsDisplay on new industry constructions
	uint8 close;                                          ///< NewsDisplay about closing industries
	uint8 economy;                                        ///< NewsDisplay on economical changes
	uint8 production_player;                              ///< NewsDisplay of production changes of industries affecting current player
	uint8 production_other;                               ///< NewsDisplay of production changes of industries affecting competitors
	uint8 production_nobody;                              ///< NewsDisplay of production changes of industries affecting no one
	uint8 advice;                                         ///< NewsDisplay on advice affecting the player's vehicles
	uint8 new_vehicles;                                   ///< NewsDisplay of new vehicles becoming available
	uint8 acceptance;                                     ///< NewsDisplay on changes affecting the acceptance of cargo at stations
	uint8 subsidies;                                      ///< NewsDisplay of changes on subsidies
	uint8 general;                                        ///< NewsDisplay of other topics
};

/** All settings related to the network. */
struct NetworkSettings {
	uint16      sync_freq;                                ///< how often do we check whether we are still in-sync
	uint8       frame_freq;                               ///< how often do we send commands to the clients
	uint16      commands_per_frame;                       ///< how many commands may be sent each frame_freq frames?
	uint16      max_commands_in_queue;                    ///< how many commands may there be in the incoming queue before dropping the connection?
	uint16      bytes_per_frame;                          ///< how many bytes may, over a long period, be received per frame?
	uint16      bytes_per_frame_burst;                    ///< how many bytes may, over a short period, be received?
	uint16      max_init_time;                            ///< maximum amount of time, in game ticks, a client may take to initiate joining
	uint16      max_join_time;                            ///< maximum amount of time, in game ticks, a client may take to sync up during joining
	uint16      max_download_time;                        ///< maximum amount of time, in game ticks, a client may take to download the map
	uint16      max_password_time;                        ///< maximum amount of time, in game ticks, a client may take to enter the password
	uint16      max_lag_time;                             ///< maximum amount of time, in game ticks, a client may be lagging behind the server
	bool        pause_on_join;                            ///< pause the game when people join
	uint16      server_port;                              ///< port the server listens on
	uint16      server_admin_port;                        ///< port the server listens on for the admin network
	bool        server_admin_chat;                        ///< allow private chat for the server to be distributed to the admin network
	ServerGameType server_game_type;                      ///< Server type: local / public / invite-only.
	std::string server_invite_code;                       ///< Invite code to use when registering as server.
	std::string server_invite_code_secret;                ///< Secret to proof we got this invite code from the Game Coordinator.
	std::string server_name;                              ///< name of the server
	std::string server_password;                          ///< password for joining this server
	std::string rcon_password;                            ///< password for rconsole (server side)
	std::string admin_password;                           ///< password for the admin network
	std::string settings_password;                        ///< password for game settings (server side)
	std::string client_name;                              ///< name of the player (as client)
	std::string default_company_pass;                     ///< default password for new companies in encrypted form
	std::string connect_to_ip;                            ///< default for the "Add server" query
	std::string network_id;                               ///< network ID for servers
	std::string company_password_storage_token;           ///< company password storage token
	std::string company_password_storage_secret;          ///< company password storage secret
	bool        autoclean_companies;                      ///< automatically remove companies that are not in use
	uint8       autoclean_unprotected;                    ///< remove passwordless companies after this many months
	uint8       autoclean_protected;                      ///< remove the password from passworded companies after this many months
	uint8       autoclean_novehicles;                     ///< remove companies with no vehicles after this many months
	uint8       max_companies;                            ///< maximum amount of companies
	uint8       max_clients;                              ///< maximum amount of clients
	Year        restart_game_year;                        ///< year the server restarts
	uint8       min_active_clients;                       ///< minimum amount of active clients to unpause the game
	bool        reload_cfg;                               ///< reload the config file before restarting
	std::string last_joined;                              ///< Last joined server
	bool        no_http_content_downloads;                     ///< do not do content downloads over HTTP
	UseRelayService use_relay_service;                    ///< Use relay service?
};

/** Settings related to the creation of games. */
struct GameCreationSettings {
	uint32 generation_seed;                  ///< noise seed for world generation
	uint32 generation_unique_id;             ///< random id to differentiate savegames
	Year   starting_year;                    ///< starting date
	Year   ending_year;                      ///< scoring end date
	uint8  map_x;                            ///< X size of map
	uint8  map_y;                            ///< Y size of map
	byte   land_generator;                   ///< the landscape generator
	byte   oil_refinery_limit;               ///< distance oil refineries allowed from map edge
	byte   snow_line_height;                 ///< the configured snow line height (deduced from "snow_coverage")
	byte   snow_coverage;                    ///< the amount of snow coverage on the map
	byte   rainforest_line_height;           ///< the configured rainforest line height
	byte   desert_coverage;                  ///< the amount of desert coverage on the map
	byte   climate_threshold_mode;           ///< climate threshold mode
	byte   heightmap_height;                 ///< highest mountain for heightmap (towards what it scales)
	byte   tgen_smoothness;                  ///< how rough is the terrain from 0-3
	byte   tree_placer;                      ///< the tree placer algorithm
	byte   heightmap_rotation;               ///< rotation director for the heightmap
	byte   se_flat_world_height;             ///< land height a flat world gets in SE
	byte   town_name;                        ///< the town name generator used for town names
	byte   landscape;                        ///< the landscape we're currently in
	byte   water_borders;                    ///< bitset of the borders that are water
	uint16 custom_town_number;               ///< manually entered number of towns
	uint16 custom_industry_number;           ///< manually entered number of industries
	byte   variety;                          ///< variety level applied to TGP
	byte   custom_terrain_type;              ///< manually entered height for TGP to aim for
	byte   custom_sea_level;                 ///< manually entered percentage of water in the map
	byte   min_river_length;                 ///< the minimum river length
	byte   river_route_random;               ///< the amount of randomicity for the route finding
	byte   amount_of_rivers;                 ///< the amount of rivers
	bool   rivers_top_of_hill;               ///< do rivers require starting near the tops of hills?
	uint8  river_tropics_width;              ///< the configured width of tropics around rivers
	uint8  lake_tropics_width;               ///< the configured width of tropics around lakes
	uint8  coast_tropics_width;              ///< the configured width of tropics around coasts
	uint8  lake_size;                        ///< how large can lakes get?
	bool   lakes_allowed_in_deserts;         ///< are lakes allowed in deserts?
	uint8  amount_of_rocks;                  ///< the amount of rocks
	uint8  height_affects_rocks;             ///< the affect that map height has on rocks
	uint8  build_public_roads;               ///< build public roads connecting towns
};

/** Settings related to construction in-game */
struct ConstructionSettings {
	uint8  map_height_limit;                 ///< the maximum allowed heightlevel
	bool   build_on_slopes;                  ///< allow building on slopes
	bool   autoslope;                        ///< allow terraforming under things
	uint16 max_bridge_length;                ///< maximum length of bridges
	byte   max_bridge_height;                ///< maximum height of bridges
	uint16 max_tunnel_length;                ///< maximum length of tunnels
	byte   train_signal_side;                ///< show signals on left / driving / right side
	bool   extra_dynamite;                   ///< extra dynamite
	bool   road_stop_on_town_road;           ///< allow building of drive-through road stops on town owned roads
	bool   road_stop_on_competitor_road;     ///< allow building of drive-through road stops on roads owned by competitors
	uint8  raw_industry_construction;        ///< type of (raw) industry construction (none, "normal", prospecting)
	uint8  industry_platform;                ///< the amount of flat land around an industry
	bool   freeform_edges;                   ///< allow terraforming the tiles at the map edges
	uint8  extra_tree_placement;             ///< (dis)allow building extra trees in-game
	uint8  trees_around_snow_line_range;     ///< range around snowline for mixed and arctic forest.
	bool   trees_around_snow_line_enabled;   ///< enable mixed and arctic forest around snowline, and no trees above snowline
	uint8  trees_around_snow_line_dynamic_range; ///< how much of the snow line dynamic range to use as the snowline for arctic tree placement
	uint8  command_pause_level;              ///< level/amount of commands that can't be executed while paused
	uint16 maximum_signal_evaluations;       ///< maximum number of programmable pre-signals which may be evaluated in one pass
	bool   enable_build_river;               ///< enable building rivers in-game
	bool   enable_remove_water;              ///< enable removing sea and rivers in-game
	uint8  road_custom_bridge_heads;         ///< allow construction of road custom bridge heads
	bool   chunnel;                          ///< allow construction of tunnels under water
	uint8  rail_custom_bridge_heads;         ///< allow construction of rail custom bridge heads
	bool   allow_grf_objects_under_bridges;  ///< allow all NewGRF objects under bridges
	bool   allow_stations_under_bridges;     ///< allow NewGRF rail station/waypoint tiles that do not specify clearance under bridges
	bool   allow_road_stops_under_bridges;   ///< allow road/tram stops under bridges
	bool   allow_docks_under_bridges;        ///< allow docks under bridges
	byte   purchase_land_permitted;          ///< whether and how purchasing land is permitted
	bool   build_object_area_permitted;      ///< whether building objects by area is permitted
	Year   no_expire_objects_after;          ///< do not expire objects after this year
	bool   ignore_object_intro_dates;        ///< allow players to build objects before their introduction dates (does not include during map generation)

	uint32 terraform_per_64k_frames;         ///< how many tile heights may, over a long period, be terraformed per 65536 frames?
	uint16 terraform_frame_burst;            ///< how many tile heights may, over a short period, be terraformed?
	uint32 clear_per_64k_frames;             ///< how many tiles may, over a long period, be cleared per 65536 frames?
	uint16 clear_frame_burst;                ///< how many tiles may, over a short period, be cleared?
	uint32 tree_per_64k_frames;              ///< how many trees may, over a long period, be planted per 65536 frames?
	uint16 tree_frame_burst;                 ///< how many trees may, over a short period, be planted?
	uint32 purchase_land_per_64k_frames;     ///< how many tiles may, over a long period, be purchased per 65536 frames?
	uint16 purchase_land_frame_burst;        ///< how many tiles may, over a short period, be purchased?
	uint32 build_object_per_64k_frames;      ///< how many tiles may, over a long period, have objects built on them per 65536 frames?
	uint16 build_object_frame_burst;         ///< how many tiles may, over a short period, have objects built on them?
	uint8  tree_growth_rate;                 ///< tree growth rate

	byte   old_simulated_wormhole_signals;   ///< moved to company settings: simulate signals in tunnel
};

/** Settings related to the AI. */
struct AISettings {
	bool   ai_in_multiplayer;                ///< so we allow AIs in multiplayer
	bool   ai_disable_veh_train;             ///< disable types for AI
	bool   ai_disable_veh_roadveh;           ///< disable types for AI
	bool   ai_disable_veh_aircraft;          ///< disable types for AI
	bool   ai_disable_veh_ship;              ///< disable types for AI
};

/** Settings related to scripts. */
struct ScriptSettings {
	uint8  settings_profile;                 ///< difficulty profile to set initial settings of scripts, esp. random AIs
	uint32 script_max_opcode_till_suspend;   ///< max opcode calls till scripts will suspend
	uint32 script_max_memory_megabytes;      ///< limit on memory a single script instance may have allocated
};

/** Settings related to the new pathfinder. */
struct NPFSettings {
	/**
	 * The maximum amount of search nodes a single NPF run should take. This
	 * limit should make sure performance stays at acceptable levels at the cost
	 * of not being perfect anymore.
	 */
	uint32 npf_max_search_nodes;
	uint32 maximum_go_to_depot_penalty;      ///< What is the maximum penalty that may be endured for going to a depot

	uint32 npf_rail_firstred_penalty;        ///< the penalty for when the first signal is red (and it is not an exit or combo signal)
	uint32 npf_rail_firstred_exit_penalty;   ///< the penalty for when the first signal is red (and it is an exit or combo signal)
	uint32 npf_rail_lastred_penalty;         ///< the penalty for when the last signal is red
	uint32 npf_rail_station_penalty;         ///< the penalty for station tiles
	uint32 npf_rail_slope_penalty;           ///< the penalty for sloping upwards
	uint32 npf_rail_curve_penalty;           ///< the penalty for curves
	uint32 npf_rail_depot_reverse_penalty;   ///< the penalty for reversing in depots
	uint32 npf_rail_pbs_cross_penalty;       ///< the penalty for crossing a reserved rail track
	uint32 npf_rail_pbs_signal_back_penalty; ///< the penalty for passing a pbs signal from the backside
	uint32 npf_buoy_penalty;                 ///< the penalty for going over (through) a buoy
	uint32 npf_water_curve_penalty;          ///< the penalty for curves
	uint32 npf_road_curve_penalty;           ///< the penalty for curves
	uint32 npf_crossing_penalty;             ///< the penalty for level crossings
	uint32 npf_road_drive_through_penalty;   ///< the penalty for going through a drive-through road stop
	uint32 npf_road_dt_occupied_penalty;     ///< the penalty multiplied by the fill percentage of a drive-through road stop
	uint32 npf_road_bay_occupied_penalty;    ///< the penalty multiplied by the fill percentage of a road bay
};

/** Settings related to the yet another pathfinder. */
struct YAPFSettings {
	bool   disable_node_optimization;        ///< whether to use exit-dir instead of trackdir in node key
	uint32 max_search_nodes;                 ///< stop path-finding when this number of nodes visited
	uint32 maximum_go_to_depot_penalty;      ///< What is the maximum penalty that may be endured for going to a depot
	bool   ship_use_yapf;                    ///< use YAPF for ships
	bool   road_use_yapf;                    ///< use YAPF for road
	bool   rail_use_yapf;                    ///< use YAPF for rail
	uint32 road_slope_penalty;               ///< penalty for up-hill slope
	uint32 road_curve_penalty;               ///< penalty for curves
	uint32 road_crossing_penalty;            ///< penalty for level crossing
	uint32 road_stop_penalty;                ///< penalty for going through a drive-through road stop
	uint32 road_stop_occupied_penalty;       ///< penalty multiplied by the fill percentage of a drive-through road stop
	uint32 road_stop_bay_occupied_penalty;   ///< penalty multiplied by the fill percentage of a road bay
	bool   rail_firstred_twoway_eol;         ///< treat first red two-way signal as dead end
	uint32 rail_firstred_penalty;            ///< penalty for first red signal
	uint32 rail_firstred_exit_penalty;       ///< penalty for first red exit signal
	uint32 rail_lastred_penalty;             ///< penalty for last red signal
	uint32 rail_lastred_exit_penalty;        ///< penalty for last red exit signal
	uint32 rail_station_penalty;             ///< penalty for non-target station tile
	uint32 rail_slope_penalty;               ///< penalty for up-hill slope
	uint32 rail_curve45_penalty;             ///< penalty for curve
	uint32 rail_curve90_penalty;             ///< penalty for 90-deg curve
	uint32 rail_depot_reverse_penalty;       ///< penalty for reversing in the depot
	uint32 rail_crossing_penalty;            ///< penalty for level crossing
	uint32 rail_look_ahead_max_signals;      ///< max. number of signals taken into consideration in look-ahead load balancer
	int32  rail_look_ahead_signal_p0;        ///< constant in polynomial penalty function
	int32  rail_look_ahead_signal_p1;        ///< constant in polynomial penalty function
	int32  rail_look_ahead_signal_p2;        ///< constant in polynomial penalty function
	uint32 rail_pbs_cross_penalty;           ///< penalty for crossing a reserved tile
	uint32 rail_pbs_station_penalty;         ///< penalty for crossing a reserved station tile
	uint32 rail_pbs_signal_back_penalty;     ///< penalty for passing a pbs signal from the backside
	uint32 rail_doubleslip_penalty;          ///< penalty for passing a double slip switch

	uint32 rail_longer_platform_penalty;           ///< penalty for longer  station platform than train
	uint32 rail_longer_platform_per_tile_penalty;  ///< penalty for longer  station platform than train (per tile)
	uint32 rail_shorter_platform_penalty;          ///< penalty for shorter station platform than train
	uint32 rail_shorter_platform_per_tile_penalty; ///< penalty for shorter station platform than train (per tile)
	uint32 ship_curve45_penalty;                   ///< penalty for 45-deg curve for ships
	uint32 ship_curve90_penalty;                   ///< penalty for 90-deg curve for ships
};

/** Settings related to all pathfinders. */
struct PathfinderSettings {
	uint8  pathfinder_for_trains;            ///< the pathfinder to use for trains
	uint8  pathfinder_for_roadvehs;          ///< the pathfinder to use for roadvehicles
	uint8  pathfinder_for_ships;             ///< the pathfinder to use for ships
	bool   new_pathfinding_all;              ///< use the newest pathfinding algorithm for all

	bool   roadveh_queue;                    ///< buggy road vehicle queueing
	bool   forbid_90_deg;                    ///< forbid trains to make 90 deg turns
	bool   back_of_one_way_pbs_waiting_point;///< whether the back of one-way PBS signals is a safe waiting point
	uint8  reroute_rv_on_layout_change;      ///< whether to re-route road vehicles when the layout changes

	bool   reverse_at_signals;               ///< whether to reverse at signals at all
	byte   wait_oneway_signal;               ///< waitingtime in days before a oneway signal
	byte   wait_twoway_signal;               ///< waitingtime in days before a twoway signal

	bool   reserve_paths;                    ///< always reserve paths regardless of signal type.
	byte   wait_for_pbs_path;                ///< how long to wait for a path reservation.
	byte   path_backoff_interval;            ///< ticks between checks for a free path.

	NPFSettings  npf;                        ///< pathfinder settings for the new pathfinder
	YAPFSettings yapf;                       ///< pathfinder settings for the yet another pathfinder
};

/** Settings related to orders. */
struct OrderSettings {
	bool   improved_load;                    ///< improved loading algorithm
	bool   gradual_loading;                  ///< load vehicles gradually
	bool   selectgoods;                      ///< only send the goods to station if a train has been there
	bool   no_servicing_if_no_breakdowns;    ///< don't send vehicles to depot when breakdowns are disabled
	bool   serviceathelipad;                 ///< service helicopters at helipads automatically (no need to send to depot)
	bool   nonstop_only;                     ///< allow non-stop orders only

	uint8  old_occupancy_smoothness;         ///< moved to company settings: percentage smoothness of occupancy measurement changes
	bool   old_timetable_separation;         ///< moved to company settings: whether to perform automatic separation based on timetable
	uint8  old_timetable_separation_rate;    ///< moved to company settings: percentage of timetable separation change to apply
};

/** Settings related to vehicles. */
struct VehicleSettings {
	uint8  max_train_length;                 ///< maximum length for trains
	uint8  smoke_amount;                     ///< amount of smoke/sparks locomotives produce
	uint8  train_acceleration_model;         ///< realistic acceleration for trains
	uint8  train_braking_model;              ///< braking model for trains
	uint8  realistic_braking_aspect_limited; ///< realistic braking lookahead is aspect limited
	uint8  roadveh_acceleration_model;       ///< realistic acceleration for road vehicles
	uint8  train_slope_steepness;            ///< Steepness of hills for trains when using realistic acceleration
	uint8  roadveh_slope_steepness;          ///< Steepness of hills for road vehicles when using realistic acceleration
	bool   wagon_speed_limits;               ///< enable wagon speed limits
	bool   train_speed_adaptation;           ///< Faster trains slow down when behind slower trains
	bool   slow_road_vehicles_in_curves;     ///< Road vehicles slow down in curves.
	bool   disable_elrails;                  ///< when true, the elrails are disabled
	UnitID max_trains;                       ///< max trains in game per company
	UnitID max_roadveh;                      ///< max trucks in game per company
	UnitID max_aircraft;                     ///< max planes in game per company
	UnitID max_ships;                        ///< max ships in game per company
	uint8  plane_speed;                      ///< divisor for speed of aircraft
	uint8  freight_trains;                   ///< value to multiply the weight of cargo by
	bool   dynamic_engines;                  ///< enable dynamic allocation of engine data
	bool   never_expire_vehicles;            ///< never expire vehicles
	Year   no_expire_vehicles_after;         ///< do not expire vehicles after this year
	Year   no_introduce_vehicles_after;      ///< do not introduce vehicles after this year
	byte   extend_vehicle_life;              ///< extend vehicle life by this many years
	byte   road_side;                        ///< the side of the road vehicles drive on
	uint8  plane_crashes;                    ///< number of plane crashes, 0 = none, 1 = reduced, 2 = normal
	bool   adjacent_crossings;               ///< enable closing of adjacent level crossings
	bool   safer_crossings;                  ///< enable safer level crossings
	bool   improved_breakdowns;              ///< different types, chances and severities of breakdowns
	bool   pay_for_repair;                   ///< pay for repairing vehicle
	uint8  repair_cost;                      ///< cost of repairing vehicle
	bool   ship_collision_avoidance;         ///< ships try to avoid colliding with each other
	bool   no_train_crash_other_company;     ///< trains cannot crash with trains from other companies
	bool   roadveh_articulated_overtaking;   ///< enable articulated road vehicles overtaking other vehicles
	bool   roadveh_cant_quantum_tunnel;      ///< enable or disable vehicles quantum tunelling through over vehicles when blocked
	bool   drive_through_train_depot;        ///< enable drive-through train depot emulation
	uint16 through_load_speed_limit;         ///< maximum speed for through load
	uint16 rail_depot_speed_limit;           ///< maximum speed entering/existing rail depots
};

/** Settings related to the economy. */
struct EconomySettings {
	bool   inflation;                        ///< disable inflation
	bool   inflation_fixed_dates;            ///< whether inflation is applied between fixed dates
	bool   bribe;                            ///< enable bribing the local authority
	EconomyType type;                        ///< economy type (original/smooth/frozen)
	bool   allow_shares;                     ///< allow the buying/selling of shares
	uint8  min_years_for_shares;             ///< minimum age of a company for it to trade shares
	uint8  feeder_payment_share;             ///< percentage of leg payment to virtually pay in feeder systems
	byte   dist_local_authority;             ///< distance for town local authority, default 20
	bool   exclusive_rights;                 ///< allow buying exclusive rights
	bool   fund_buildings;                   ///< allow funding new buildings
	bool   fund_roads;                       ///< allow funding local road reconstruction
	bool   give_money;                       ///< allow giving other companies money
	bool   mod_road_rebuild;                 ///< roadworks remove unnecessary RoadBits
	bool   multiple_industry_per_town;       ///< allow many industries of the same type per town
	int8   town_growth_rate;                 ///< town growth rate
	uint8  town_growth_cargo_transported;    ///< percentage of town growth rate which depends on proportion of transported cargo in the last month
	bool   town_zone_calc_mode;              ///< calc mode for town zones
	uint16 town_zone_0_mult;                 ///< multiplier for the size of town zone 0
	uint16 town_zone_1_mult;                 ///< multiplier for the size of town zone 1
	uint16 town_zone_2_mult;                 ///< multiplier for the size of town zone 2
	uint16 town_zone_3_mult;                 ///< multiplier for the size of town zone 3
	uint16 town_zone_4_mult;                 ///< multiplier for the size of town zone 4
	uint16 city_zone_0_mult;                 ///< multiplier for the size of city zone 0
	uint16 city_zone_1_mult;                 ///< multiplier for the size of city zone 1
	uint16 city_zone_2_mult;                 ///< multiplier for the size of city zone 2
	uint16 city_zone_3_mult;                 ///< multiplier for the size of city zone 3
	uint16 city_zone_4_mult;                 ///< multiplier for the size of city zone 4
	uint8  larger_towns;                     ///< the number of cities to build. These start off larger and grow twice as fast
	uint8  initial_city_size;                ///< multiplier for the initial size of the cities compared to towns
	TownLayout town_layout;                  ///< select town layout, @see TownLayout
	TownCargoGenMode town_cargogen_mode;     ///< algorithm for generating cargo from houses, @see TownCargoGenMode
	bool   allow_town_roads;                 ///< towns are allowed to build roads (always allowed when generating world / in SE)
	uint16  town_min_distance;               ///< minimum distance between towns
	uint8  max_town_heightlevel;             ///< maximum height level for towns
	uint16 min_town_land_area;               ///< minimum contiguous lang area for towns.
	uint16 min_city_land_area;               ///< minimum contiguous lang area for cities.
	TownFounding found_town;                 ///< town founding.
	bool   station_noise_level;              ///< build new airports when the town noise level is still within accepted limits
	uint16 town_noise_population[3];         ///< population to base decision on noise evaluation (@see town_council_tolerance)
	bool   infrastructure_sharing[4];        ///< enable infrastructure sharing for rail/road/water/air
	uint   sharing_fee[4];                   ///< fees for infrastructure sharing for rail/road/water/air
	bool   sharing_payment_in_debt;          ///< allow fee payment for companies with more loan than money (switch off to prevent MP exploits)
	bool   allow_town_level_crossings;       ///< towns are allowed to build level crossings
	TownTunnelMode town_build_tunnels;       ///< if/when towns are allowed to build road tunnels
	uint8  town_max_road_slope;              ///< maximum number of consecutive sloped road tiles which towns are allowed to build
	bool   allow_town_bridges;               ///< towns are allowed to build bridges
	int8   old_town_cargo_factor;            ///< old power-of-two multiplier for town (passenger, mail) generation. May be negative.
	int16  town_cargo_scale_factor;          ///< scaled power-of-two multiplier for town (passenger, mail) generation. May be negative.
	int16  industry_cargo_scale_factor;      ///< scaled power-of-two multiplier for primary industry generation. May be negative.
	bool   infrastructure_maintenance;       ///< enable monthly maintenance fee for owner infrastructure
	uint8  day_length_factor;                ///< factor which the length of day is multiplied
	uint16 random_road_reconstruction;       ///< chance out of 1000 per tile loop for towns to start random road re-construction
	bool disable_inflation_newgrf_flag;      ///< Disable NewGRF inflation flag
	CargoPaymentAlgorithm payment_algorithm; ///< Cargo payment algorithm
	TickRateMode tick_rate;                  ///< Tick rate mode
};

struct LinkGraphSettings {
	uint16 recalc_time;                         ///< time (in days) for recalculating each link graph component.
	uint16 recalc_interval;                     ///< time (in days) between subsequent checks for link graphs to be calculated.
	bool recalc_not_scaled_by_daylength;        ///< whether the time should be in daylength-scaled days (false) or unscaled days (true)
	DistributionType distribution_pax;          ///< distribution type for passengers
	DistributionType distribution_mail;         ///< distribution type for mail
	DistributionType distribution_armoured;     ///< distribution type for armoured cargo class
	DistributionType distribution_default;      ///< distribution type for all other goods
	DistributionType distribution_per_cargo[NUM_CARGO]; ///< per cargo distribution types
	uint8 accuracy;                             ///< accuracy when calculating things on the link graph. low accuracy => low running time
	uint8 demand_size;                          ///< influence of supply ("station size") on the demand function
	uint8 demand_distance;                      ///< influence of distance between stations on the demand function
	uint8 short_path_saturation;                ///< percentage up to which short paths are saturated before saturating most capacious paths
	uint16 aircraft_link_scale;                 ///< scale effective distance of aircraft links

	inline DistributionType GetDistributionType(CargoID cargo) const {
		if (this->distribution_per_cargo[cargo] != DT_PER_CARGO_DEFAULT) return this->distribution_per_cargo[cargo];
		if (IsCargoInClass(cargo, CC_PASSENGERS)) return this->distribution_pax;
		if (IsCargoInClass(cargo, CC_MAIL)) return this->distribution_mail;
		if (IsCargoInClass(cargo, CC_ARMOURED)) return this->distribution_armoured;
		return this->distribution_default;
	}
};

/** Settings related to stations. */
struct StationSettings {
	bool   modified_catchment;               ///< different-size catchment areas
	bool   serve_neutral_industries;         ///< company stations can serve industries with attached neutral stations
	bool   adjacent_stations;                ///< allow stations to be built directly adjacent to other stations
	bool   distant_join_stations;            ///< allow to join non-adjacent stations
	bool   never_expire_airports;            ///< never expire airports
	byte   station_spread;                   ///< amount a station may spread
	byte   catchment_increase;               ///< amount by which station catchment is increased
	bool   cargo_class_rating_wait_time;     ///< station rating tolerance to time since last cargo pickup depends on cargo class
	bool   station_size_rating_cargo_amount; ///< station rating tolerance to waiting cargo amount depends on station size
	StationDelivery station_delivery_mode;   ///< method to use for distributing cargo from stations to accepting industries
};

/** Default settings for vehicles. */
struct VehicleDefaultSettings {
	bool   servint_ispercent;                ///< service intervals are in percents
	uint16 servint_trains;                   ///< service interval for trains
	uint16 servint_roadveh;                  ///< service interval for road vehicles
	uint16 servint_aircraft;                 ///< service interval for aircraft
	uint16 servint_ships;                    ///< service interval for ships
	bool   auto_timetable_by_default;        ///< use automatic timetables by default
	bool   auto_separation_by_default;       ///< use automatic timetable separation by default
};

/** Settings that can be set per company. */
struct CompanySettings {
	bool engine_renew;                       ///< is autorenew enabled
	int16 engine_renew_months;               ///< months before/after the maximum vehicle age a vehicle should be renewed
	uint32 engine_renew_money;               ///< minimum amount of money before autorenew is used
	bool renew_keep_length;                  ///< sell some wagons if after autoreplace the train is longer than before
	VehicleDefaultSettings vehicle;          ///< default settings for vehicles
	uint8 order_occupancy_smoothness;        ///< percentage smoothness of occupancy measurement changes
	uint8  auto_timetable_separation_rate;   ///< percentage of auto timetable separation change to apply
	bool infra_others_buy_in_depot[4];       ///< other companies can buy/autorenew in this companies depots (where infra sharing enabled)
	uint16 timetable_autofill_rounding;      ///< round up timetable times to be a multiple of this number of ticks
	bool advance_order_on_clone;             ///< when cloning a vehicle or copying/sharing an order list, advance the current order to a suitable point
	bool copy_clone_add_to_group;            ///< whether to add cloned vehicles to the source vehicle's group, when cloning a vehicle without sharing orders
	bool remain_if_next_order_same_station;  ///< if the next order is for the same station, start loading/unloading again instead of leaving.

	byte old_simulated_wormhole_signals;     ///< no longer needs a setting: tunnel/bridge signal simulation spacing
};

/** Debug settings. */
struct DebugSettings {
	uint32 chicken_bits;                     ///< chicken bits
	uint32 newgrf_optimiser_flags;           ///< NewGRF optimiser flags
};

/** Scenario editor settings. */
struct ScenarioSettings {
	bool multiple_buildings;                 ///< allow manually adding more than one church/stadium
	bool house_ignore_dates;                 ///< allow manually adding houses regardless of date restrictions
	uint8 house_ignore_zones;                ///< allow manually adding houses regardless of zone restrictions
	bool house_ignore_grf;                   ///< allow manually adding houses regardless of GRF restrictions
};

/** Settings related to currency/unit systems. */
struct ClientLocaleSettings {
	bool sync_locale_network_server;         ///< sync locale settings with network server
};

/** All settings together for the game. */
struct GameSettings {
	DifficultySettings   difficulty;         ///< settings related to the difficulty
	GameCreationSettings game_creation;      ///< settings used during the creation of a game (map)
	ConstructionSettings construction;       ///< construction of things in-game
	AISettings           ai;                 ///< what may the AI do?
	ScriptSettings       script;             ///< settings for scripts
	class AIConfig      *ai_config[MAX_COMPANIES]; ///< settings per company
	class GameConfig    *game_config;        ///< settings for gamescript
	PathfinderSettings   pf;                 ///< settings for all pathfinders
	OrderSettings        order;              ///< settings related to orders
	VehicleSettings      vehicle;            ///< options for vehicles
	EconomySettings      economy;            ///< settings to change the economy
	LinkGraphSettings    linkgraph;          ///< settings for link graph calculations
	StationSettings      station;            ///< settings related to station management
	LocaleSettings       locale;             ///< settings related to used currency/unit system in the current game
	DebugSettings        debug;              ///< debug settings
	TimeSettings         game_time;          ///< time display settings.
};

/** All settings that are only important for the local client. */
struct ClientSettings {
	GUISettings          gui;                ///< settings related to the GUI
	ClientLocaleSettings client_locale;      ///< settings related to used currency/unit system in the client
	NetworkSettings      network;            ///< settings related to the network
	CompanySettings      company;            ///< default values for per-company settings
	SoundSettings        sound;              ///< sound effect settings
	MusicSettings        music;              ///< settings related to music/sound
	NewsSettings         news_display;       ///< news display settings.
	ScenarioSettings     scenario;           ///< scenario editor settings
};

/** The current settings for this game. */
extern ClientSettings _settings_client;

/** The current settings for this game. */
extern GameSettings _settings_game;

/** The settings values that are used for new games and/or modified in config file. */
extern GameSettings _settings_newgame;

/** The effective settings that are used for time display. */
extern TimeSettings _settings_time;

/** Old vehicle settings, which were game settings before, and are company settings now. (Needed for savegame conversion) */
extern VehicleDefaultSettings _old_vds;

/**
 * Get the settings-object applicable for the current situation: the newgame settings
 * when we're in the main menu and otherwise the settings of the current game.
 */
static inline GameSettings &GetGameSettings()
{
	return (_game_mode == GM_MENU) ? _settings_newgame : _settings_game;
}

#endif /* SETTINGS_TYPE_H */
