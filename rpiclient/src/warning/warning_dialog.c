/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * warning_dialog.c
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
#include "warning_dialog.h"

WarningDialog *new_warning_dialog(GtkWidget *parent, const gchar *msg)
{
    WarningDialog *instance = NULL;

    if (parent == NULL)
    {
        g_warning(WARNING_LOG_FAILED_PARENT_WARNINGS_DIALOG);
        return instance;
    }

    if (msg == NULL)
    {
        g_warning(WARNING_LOG_FAILED_MESSAGE_WARNINGS_DIALOG);
        return instance;
    }

    instance = g_malloc(sizeof(WarningDialog));

    if (instance)
    {
        instance->dialog = gtk_message_dialog_new(
            GTK_WINDOW(parent), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, msg
        );
    }
    else
    {
        g_warning(WARNING_LOG_FAILED_MALLOC_WARNINGS_DIALOG);
    }

    return instance;
}

void show_warning_dialog(WarningDialog *instance)
{
    if (instance == NULL)
    {
        return;
    }

    if (instance->dialog)
    {
        gtk_widget_show(instance->dialog);
        gint result = gtk_dialog_run(GTK_DIALOG(instance->dialog));

        if (result == GTK_RESPONSE_CLOSE)
        {
            hide_warning_dialog(instance);
        }
    }
}

void hide_warning_dialog(WarningDialog *instance)
{
    if (instance == NULL)
    {
        return;
    }

    if (instance->dialog)
    {
        gtk_widget_hide(instance->dialog);
    }
}

void destroy_warning_dialog(WarningDialog *instance)
{
    if (instance == NULL)
    {
        return;
    }

    gtk_widget_destroy(instance->dialog);
    g_free(instance);
}
