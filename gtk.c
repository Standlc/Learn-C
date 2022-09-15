#include <stdio.h>
#include <gtk/gtk.h>

// SET UP
// brew install gtk+3

// RUN APP
// gcc `pkg-config --cflags gtk+-3.0` -o <filename> <filename>.c `pkg-config --libs gtk+-3.0`
// ./<filename>

static void print_hello(GtkWidget *widget, gpointer data)
{
    g_print("hellow");
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    // GtkWidget *button_box;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    // gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // NEW GRID
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // BUTTON 1
    button = gtk_button_new_with_label("Button 1");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

    // BUTTON 2
    button = gtk_button_new_with_label("Button 2");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

    // BUTTON 3
    button = gtk_button_new_with_label("Quit");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);

    // button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    // gtk_container_add(GTK_CONTAINER(window), button_box);

    // button = gtk_button_new_with_label("Hello World");
    // g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
    // // g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    // gtk_container_add(GTK_CONTAINER(button_box), button);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}