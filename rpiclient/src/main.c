/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2016 - 2025 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include "resource/rpi_resource.h"
#include "home/rpi_home.h"
#include "home/rpi_menu.h"
#include "exit/rpi_exit_dialog.h"
#include "settings/rpi_settings_network_window.h"
#include "settings/rpi_settings_general_window.h"
#include "help/rpi_help_window.h"
#include "about/rpi_about_dialog.h"

RPIHome *app = NULL;

/*ServerParameters *server_parameters;*/
/*GThreadParameters *gthread_parameters;*/
gchar *resource_dir_path = NULL;
gchar *config_dir_path = NULL;

static gint on_exit(GtkWidget *widget, GdkEvent *event, gpointer data);
static void on_option_connect(void);
static void on_option_disconnect(void);
static void on_show_settings_general(void);
static void on_show_settings_network(void);
static void on_show_help(void);
static void on_show_about(void);

int main(int argc, char *argv[])
{
    // g_thread_init(NULL);
    // gdk_threads_init();
    // gdk_threads_enter();

    gtk_init(&argc, &argv);
    resource_dir_path = rpi_get_resource_dir();
    config_dir_path = rpi_get_config_dir();
    app = new_rpi_home();
    show_rpi_home(app);

    g_signal_connect(
        G_OBJECT(get_window_from_rpi_home(app)),
        "delete_event",
        G_CALLBACK(on_exit),
        NULL
    );
    g_signal_connect(
        G_OBJECT(get_exit_item_from_rpi_menu(get_menu_bar_from_rpi_home(app))),
        "activate",
        G_CALLBACK(on_exit),
        NULL
    );
    g_signal_connect(
        G_OBJECT(get_connect_item_from_rpi_menu(get_menu_bar_from_rpi_home(app))),
        "activate",
        G_CALLBACK(on_option_connect),
        NULL
    );
    g_signal_connect(
        G_OBJECT(get_disconnect_item_from_rpi_menu(get_menu_bar_from_rpi_home(app))),
        "activate",
        G_CALLBACK(on_option_disconnect),
        NULL
    );
    g_signal_connect(
        G_OBJECT(get_general_item_from_rpi_menu(get_menu_bar_from_rpi_home(app))),
        "activate",
        G_CALLBACK(on_show_settings_general),
        NULL
    );
    g_signal_connect(
        G_OBJECT(get_network_item_from_rpi_menu(get_menu_bar_from_rpi_home(app))),
        "activate",
        G_CALLBACK(on_show_settings_network),
        NULL
    );
    g_signal_connect(
        G_OBJECT(get_help_item_from_rpi_menu(get_menu_bar_from_rpi_home(app))),
        "activate",
        G_CALLBACK(on_show_help),
        NULL
    );
    g_signal_connect(
        G_OBJECT(get_about_item_from_rpi_menu(get_menu_bar_from_rpi_home(app))),
        "activate",
        G_CALLBACK(on_show_about),
        NULL
    );

    // yes_tid = g_thread_create(readSocket, NULL, FALSE, NULL);

    gtk_main();

    // gdk_threads_leave();

    return 0;
}

static gint on_exit(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    ExitDialog *exit_dialog = new_exit_dialog(get_window_from_rpi_home(app));
    gint exit_code = show_exit_dialog(exit_dialog);

    if (exit_code == CLOSE_ON_EXIT_DIALOG)
    {
        destroy_rpi_home(app);
        app = NULL;
        gtk_main_quit();
        return FALSE;
    }

    hide_exit_dialog(exit_dialog);
    destroy_exit_dialog(exit_dialog);
    exit_dialog = NULL;

    return TRUE;
}

static void on_option_connect(void)
{
    g_warning("%s", "connect\n");
}

static void on_option_disconnect(void)
{
    g_warning("%s", "disconnect\n");
}

static void on_show_settings_general(void)
{
    SettingsGeneralWindow *settings_general_window = new_settings_general_window();

    if (settings_general_window)
    {
        show_settings_general_window(settings_general_window);
    }
}

static void on_show_settings_network(void)
{
    SettingsNetworkWindow *settings_network_window = new_settings_network_window();

    if (settings_network_window)
    {
        show_settings_network_window(settings_network_window);
    }
}

static void on_show_help(void)
{
    HelpWindow *help_window = new_help_window();

    if (help_window)
    {
        show_help_window(help_window);
    }
}

static void on_show_about(void)
{
    AboutDialog *about_dialog = new_about_dialog();

    if (about_dialog)
    {
        show_about_dialog(about_dialog);
    }
}
