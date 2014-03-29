#include <gtk/gtk.h>


void
on_denyonce_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_permitonce_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_deny_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_permit_clicked                      (GtkButton       *button,
                                        gpointer         user_data);

void
on_filterentry_changed                 (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_detachbutton_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_reviewbutton_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_killbutton_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
template_ok_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_wizard_clicked                      (GtkButton       *button,
                                        gpointer         user_data);

void
on_wizard_cancel_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_wizardlist_select_child             (GtkList         *list,
                                        GtkWidget       *widget,
                                        gpointer         user_data);
