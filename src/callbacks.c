#include <sys/types.h>

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

char *freadline(char *, int, FILE *);
void wizard_cleanup(GtkWidget *);

#define MAX_WIZARDS 100

static int wizard_selected;
static int wizard_items;
static char *wizard_descriptions[MAX_WIZARDS];

void
on_denyonce_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *errorcode;
	GtkWidget *entry;

	errorcode = lookup_widget(GTK_WIDGET(button), "errorcode");
	entry = GTK_COMBO(errorcode)->entry;

	g_print("deny-now[%s]\n", gtk_entry_get_text(GTK_ENTRY(entry)));
	gtk_main_quit();
}


void
on_permitonce_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	g_print("permit-now\n");
	gtk_main_quit();
}


void
on_deny_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *errorcode;
	GtkWidget *entry;

	errorcode = lookup_widget(GTK_WIDGET(button), "errorcode");
	entry = GTK_COMBO(errorcode)->entry;

	g_print("deny[%s]\n", gtk_entry_get_text(GTK_ENTRY(entry)));
	gtk_main_quit();
}


void
on_permit_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{

	g_print("permit\n");
	gtk_main_quit();
}


void
on_filterentry_changed                 (GtkEditable     *editable,
                                        gpointer         user_data)
{
	g_print("%s\n", gtk_entry_get_text(GTK_ENTRY(editable)));

	gtk_main_quit();
}

void
on_detachbutton_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	g_print("detach\n");

	gtk_main_quit();
}


void
on_reviewbutton_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	extern GtkWidget *filterreview;
	GList *items = NULL;
	GtkWidget *list_item;
	GtkWidget *list;
	char line[1024];

	list = lookup_widget(GTK_WIDGET(filterreview), "filterlist");

	g_print("review\n");

	while (freadline(line, sizeof(line), stdin)) {
		if (!strcmp(line, "WRONG"))
			break;
		if (!isdigit(line[0]))
			continue;
		list_item = gtk_list_item_new_with_label(line);
		gtk_widget_show(list_item);
		items = g_list_append(items, list_item);
	}

	gtk_list_append_items(GTK_LIST(list), items);
	gtk_widget_show(filterreview);
}


void
on_okbutton_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	extern GtkWidget *filterreview;
	GtkWidget *list;

	list = lookup_widget(GTK_WIDGET(filterreview), "filterlist");

	gtk_widget_hide(filterreview);

	gtk_list_clear_items(GTK_LIST(list), 0, -1);
}


void
on_killbutton_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	g_print("kill\n");

	gtk_main_quit();
}


void
wizard_cleanup(GtkWidget *wizard)
{
	extern GtkWidget *wizardbutton;
	GtkWidget *list;
	int i;

	list = lookup_widget(GTK_WIDGET(wizard), "wizardlist");

	gtk_widget_hide(wizard);

	gtk_list_clear_items(GTK_LIST(list), 0, -1);

	for (i = 0; i < wizard_items; i++) {
		free(wizard_descriptions[i]);
		wizard_descriptions[i] = NULL;
	}
	wizard_items = 0;

	gtk_widget_set_sensitive(wizardbutton, 1);
}

void
template_ok_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	extern GtkWidget *wizard;

	wizard_cleanup(wizard);

	g_print("template %d\n", wizard_selected + 1);

	gtk_main_quit();
}


void
on_wizard_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
	extern GtkWidget *wizardbutton;
	extern GtkWidget *wizard;
	GList *items = NULL;
	GtkWidget *list_item;
	GtkWidget *list;
	char line[1024];
	int i = 0;

	gtk_widget_set_sensitive(wizardbutton, 0);

	list = lookup_widget(GTK_WIDGET(wizard), "wizardlist");

	g_print("templates\n");

	wizard_items = 0;
	while (freadline(line, sizeof(line), stdin) && i < MAX_WIZARDS) {
		char *split;

		if (!strcmp(line, "WRONG"))
			break;
		if (!isdigit(line[0]))
			continue;

		split = strstr(line, " - ");
		if (split == NULL)
			break;

		*split = '\0';
		split += 3;

		if ((wizard_descriptions[wizard_items]=strdup(split)) == NULL)
			break;
		wizard_items++;

		i++;
		list_item = gtk_list_item_new_with_label(line);
		gtk_widget_show(list_item);
		items = g_list_append(items, list_item);
	}

	gtk_list_append_items(GTK_LIST(list), items);

	if (!i)
		return;

	gtk_list_select_item(GTK_LIST(list), 0);

	gtk_widget_show(wizard);
}


void
on_wizard_cancel_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	extern GtkWidget *wizard;

	wizard_cleanup(wizard);
}


void
on_wizardlist_select_child             (GtkList         *list,
                                        GtkWidget       *widget,
                                        gpointer         user_data)
{
	extern GtkWidget *wizard;
	GtkWidget *label;

	label = lookup_widget(GTK_WIDGET(wizard), "description");

	wizard_selected = gtk_list_child_position(list, widget);

	gtk_label_set_text(GTK_LABEL(label),
	    wizard_descriptions[wizard_selected]);
}
