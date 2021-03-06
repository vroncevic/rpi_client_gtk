/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * rpichannelset.h
 * Copyright (C) 2016 Vladimir Roncevic <elektron.ronca@gmail.com>
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
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "rpichannelset.h"

RPIChannelSet * new_rpichannelset(gint channel_id) {
    RPIChannelSet *rpichannelset_ptr = g_malloc(sizeof(RPIChannelSet));
    rpichannelset_ptr->vbar_set = gtk_vb_new();
    gtk_widget_set_tooltip_text(
        rpichannelset_ptr->vbar_set, TOOLTIP_VERTICAL_BAR(channel_id)
    );
    rpichannelset_ptr->scale = gtk_vscale_new_with_range(
        MIN_VALUE_SCALE, MAX_VALUE_SCALE, STEP_VALUE_SCALE
    );
    gtk_widget_set_tooltip_text(
        rpichannelset_ptr->scale, TOOLTIP_SCALE(channel_id)
    );
    gtk_range_set_inverted(GTK_RANGE(rpichannelset_ptr->scale), TRUE);
    gtk_scale_set_value_pos(GTK_SCALE(rpichannelset_ptr->scale), GTK_POS_TOP);
    gtk_widget_set_size_request(
        rpichannelset_ptr->scale, WIDTH_SCALE, HEIGHT_SCALE
    );
    rpichannelset_ptr->spinner_adj = (GtkAdjustment *) gtk_adjustment_new(
        VALUE_SPINNER_ADJUSTMENT, LOWER_SPINNER_ADJUSTMENT,
        UPPER_SPINNER_ADJUSTMENT, STEP_INCREMENT_SPINNER_ADJUSTMENT,
        PAGE_INCREMENT_SPINNER_ADJUSTMENT, PAGE_SIZE_SPINNER_ADJUSTMENT
    );
    rpichannelset_ptr->spinner_button = gtk_spin_button_new(
        rpichannelset_ptr->spinner_adj,
        CLIMB_RATE_SPINNER_BUTTON, DIGITS_SPINNER_BUTTON
    );
    gtk_widget_set_tooltip_text(
        rpichannelset_ptr->spinner_button, TOOLTIP_SPINNER_BUTTON(channel_id)
    );
    rpichannelset_ptr->activate_gpio = gtk_check_button_new_with_label(
        TEXT_CHECK_BOX_GPIO(channel_id)
    );
    gtk_widget_set_tooltip_text(
        rpichannelset_ptr->activate_gpio, TOOLTIP_CHECK_BOX_GPIO(channel_id)
    );
    gtk_toggle_button_set_active(
        GTK_TOGGLE_BUTTON(rpichannelset_ptr->activate_gpio), FALSE
    );
    return rpichannelset_ptr;
}

void show_rpichannelset(RPIChannelSet *rpichannelset_ptr) {
    if(rpichannelset_ptr) {
        gtk_widget_show(rpichannelset_ptr->vbar_set);
        gtk_widget_show(rpichannelset_ptr->scale);
        gtk_widget_show((GtkWidget *)rpichannelset_ptr->spinner_adj);
        gtk_widget_show(rpichannelset_ptr->spinner_button);
        gtk_widget_show(rpichannelset_ptr->activate_gpio);
    }
}

void hide_rpichannelset(RPIChannelSet *rpichannelset_ptr) {
    if(rpichannelset_ptr) {
        gtk_widget_hide(rpichannelset_ptr->vbar_set);
        gtk_widget_hide(rpichannelset_ptr->scale);
        gtk_widget_hide((GtkWidget *)rpichannelset_ptr->spinner_adj);
        gtk_widget_hide(rpichannelset_ptr->spinner_button);
        gtk_widget_hide(rpichannelset_ptr->activate_gpio);
    }
}

void destroy_rpichannelset(RPIChannelSet *rpichannelset_ptr) {
    if(rpichannelset_ptr) {
        gtk_vb_destroy((GtkObject *)rpichannelset_ptr->vbar_set);
        gtk_widget_destroy(rpichannelset_ptr->scale);
        gtk_widget_destroy((GtkWidget *)rpichannelset_ptr->spinner_adj);
        gtk_widget_destroy(rpichannelset_ptr->spinner_button);
        gtk_widget_destroy(rpichannelset_ptr->activate_gpio);
        g_free(rpichannelset_ptr->vbar_set);
        g_free(rpichannelset_ptr->scale);
        g_free(rpichannelset_ptr->spinner_adj);
        g_free(rpichannelset_ptr->spinner_button);
        g_free(rpichannelset_ptr->activate_gpio);
        g_free(rpichannelset_ptr);
    }
}

