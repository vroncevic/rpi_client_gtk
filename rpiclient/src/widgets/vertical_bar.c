/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * vertical_bar.c
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
#include "vertical_bar.h"

static void gtk_vb_class_init(GtkVBClass *klass);
static void gtk_vb_init(GtkVB *vb);
static void gtk_vb_get_preferred_width(GtkWidget *widget, gint *minimum_width, gint *natural_width);
static void gtk_vb_get_preferred_height(GtkWidget *widget, gint *minimum_height, gint *natural_height);
static gboolean gtk_vb_draw(GtkWidget *widget, cairo_t *cr);

void gtk_vb_set_state(GtkVB *vb, gint num) {
    vb->sel = num;
    gtk_widget_queue_draw(GTK_WIDGET(vb));
}

GtkWidget *gtk_vb_new(void) {
    return g_object_new(gtk_vb_get_type(), NULL);
}

static void gtk_vb_class_init(GtkVBClass *klass) {
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);
    widget_class->get_preferred_width = gtk_vb_get_preferred_width;
    widget_class->get_preferred_height = gtk_vb_get_preferred_height;
    widget_class->draw = gtk_vb_draw;
}

static void gtk_vb_init(GtkVB *vb) {
    vb->sel = 0; // Initialize selection value
}

static void gtk_vb_get_preferred_width(GtkWidget *widget, gint *minimum_width, gint *natural_width) {
    *minimum_width = 80;
    *natural_width = 80;
}

static void gtk_vb_get_preferred_height(GtkWidget *widget, gint *minimum_height, gint *natural_height) {
    *minimum_height = 200; // Minimum height
    *natural_height = 200; // Natural height
}

static gboolean gtk_vb_draw(GtkWidget *widget, cairo_t *cr) {
    // Clear background
    cairo_set_source_rgb(cr, 1, 1, 1); // White background
    cairo_paint(cr);
    
    gint height = gtk_widget_get_allocated_height(widget);
    gint pos = GTK_VB(widget)->sel;
    gint rect_count = pos / 5; // Determine how many rectangles to fill

    for (gint i = 0; i < 20; i++) {
        if (i < rect_count) {
            cairo_set_source_rgb(cr, 0.6, 1.0, 0); // Filled color
        } else {
            cairo_set_source_rgb(cr, 0.2, 0.4, 0); // Empty color
        }
        cairo_rectangle(cr, 10, height - (i * 10) - 10, 60, 8); // Vertical rectangles
        cairo_fill(cr);
    }

    return FALSE; // Indicate the event has not been fully handled
}

