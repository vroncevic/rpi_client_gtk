/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * rpi_about_dialog.c
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
#include "../rpi_config.h"
#include "../resource/rpi_resource.h"
#include "rpi_about_dialog.h"

#define FAILED_MALLOC_ABOUT_DIALOG "Failed to allocate memory for about dialog.\n"
#define FAILED_PIXBUF_ABOUT_DIALOG "Failed to create pixbuf from about logo_file_path.\n"
#define FAILED_RESOURCE_ABOUT_DIALOG "Failed to get resource path for about logo_file_path.\n"

static const gchar* TEXT_NAME_ABOUT_DIALOG = "About RPIClient";
static const gchar* TEXT_VERSION_ABOUT_DIALOG = RPI_CLIENT_VERSION;
static const gchar* TEXT_COPYRIGHT_ABOUT_DIALOG = "2025 (c) elektron.ronca@gmail.com";
static const gchar* TEXT_COMMENTS_ABOUT_DIALOG = "Free Software you can redistribute it and/or modify it.";
static const gchar* TEXT_WEBSITE_ABOUT_DIALOG = "https://github.com/vroncevic/rpiclient-gtk";
static const gchar* LOGO_FILE_NAME_ABOUT_DIALOG = "logo.png";

//////////////////////////////////////////////////////////////////////////////
/// @brief About dialog complex widget
///   dialog - Gtk about dialog widget
struct _AboutDialog
{
    GtkWidget *dialog;
};

AboutDialog *new_about_dialog(void)
{
    AboutDialog *instance = g_malloc(sizeof(AboutDialog));

    if(!instance)
    {
        g_critical(FAILED_MALLOC_ABOUT_DIALOG);
        return NULL;
    }

    instance->dialog = gtk_about_dialog_new();

    if (!GTK_IS_ABOUT_DIALOG(instance->dialog))
    {
        g_critical(FAILED_MALLOC_ABOUT_DIALOG);
        destroy_about_dialog(instance);
        return NULL;
    }

    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(instance->dialog), TEXT_NAME_ABOUT_DIALOG);
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(instance->dialog), TEXT_VERSION_ABOUT_DIALOG);
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(instance->dialog), TEXT_COPYRIGHT_ABOUT_DIALOG);
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(instance->dialog), TEXT_COMMENTS_ABOUT_DIALOG);
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(instance->dialog), TEXT_WEBSITE_ABOUT_DIALOG);
    gchar *logo_file_path = rpi_get_resource_file_path(LOGO_FILE_NAME_ABOUT_DIALOG);

    if (logo_file_path)
    {
        GdkPixbuf *pixbuf = rpi_cpixbuf(logo_file_path);

        if (GDK_IS_PIXBUF(pixbuf))
        {
            gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(instance->dialog), pixbuf);
            g_object_unref(pixbuf);
            pixbuf = NULL;
        }
        else
        {
            g_warning(FAILED_PIXBUF_ABOUT_DIALOG);
            pixbuf = NULL;
        }

        g_free(logo_file_path);
        logo_file_path = NULL;
    }
    else
    {
        g_warning(FAILED_RESOURCE_ABOUT_DIALOG);
        logo_file_path = NULL;
    }

    g_signal_connect_swapped(
        G_OBJECT(instance->dialog), "response", G_CALLBACK(destroy_about_dialog), instance
    );

    return instance;
}

void show_about_dialog(AboutDialog *instance)
{
    if (instance)
    {
        gboolean is_about_dialog = GTK_IS_ABOUT_DIALOG(instance->dialog);
        gboolean is_about_dialog_hidden = !gtk_widget_get_visible(GTK_WIDGET(instance->dialog));

        if (is_about_dialog && is_about_dialog_hidden)
        {
            gtk_widget_show(GTK_WIDGET(instance->dialog));
        }
    }
}

void hide_about_dialog(AboutDialog *instance)
{
    if (instance)
    {
        gboolean is_about_dialog = GTK_IS_ABOUT_DIALOG(instance->dialog);
        gboolean is_about_dialog_visible = gtk_widget_get_visible(GTK_WIDGET(instance->dialog));

        if (is_about_dialog && is_about_dialog_visible)
        {
            gtk_widget_hide(GTK_WIDGET(instance->dialog));
        }
    }
}

void destroy_about_dialog(AboutDialog *instance)
{
    if (instance)
    {
        if (GTK_IS_ABOUT_DIALOG(instance->dialog))
        {
            gtk_widget_destroy(GTK_WIDGET(instance->dialog));
            instance->dialog = NULL;
        }

        g_free(instance);
    }
}
