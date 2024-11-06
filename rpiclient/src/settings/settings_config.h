/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * settings_config.h
 * Copyright (C) 2016 - 2024 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * rpiclient-gtk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rpiclient-gtk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "../resource/resource.h"

#define CONFIGURATION_FILE_PROMPT "/config/prompt.config"
#define CONFIGURATION_FILE_SERVER_ADDRESS "/config/server_address.config"
#define CONFIGURATION_FILE_SERVER_PORT "/config/server_port.config"

//////////////////////////////////////////////////////////////////////////////
/// @brief Settings configuration structure
///   no_prompt - Configuration point for prompt
///   ip_address - Configuration point for server ip address
///   port_number - Configuration point for server port number
typedef struct
{
    gchar *no_prompt;
    gchar *ip_address;
    gchar *port_number;
} SettingsConfig;

//////////////////////////////////////////////////////////////////////////////
/// @brief Write settings configuration to file
/// @param instance is pointer to settings configuration to be written
/// @return Integer status
gint settings_write(SettingsConfig* instance);

//////////////////////////////////////////////////////////////////////////////
/// @brief Read configuration from files
/// @return Settings configuration structure pointer
SettingsConfig* settings_read(void);

//////////////////////////////////////////////////////////////////////////////
/// @brief Free settings configuration memory
/// @param instance is pointer to settings configuration to be free
void settings_free(SettingsConfig* instance);
