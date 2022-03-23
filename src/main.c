#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define false 0
#define true 1
#define null 0

//gtk_label_new("");
//gtk_button_new_with_label("");
//gtk_entry_set_placeholder_text(GTK_ENTRY(entry),"placeholder");
//gtk_entry_new();
//gtk_widget_set_size_request(wiget, x, y);
//gtk_entry_set_visibility(GTK_ENTRY(entry), bool);
//gtk_entry_get_text(GTK_ENTRY(entry)); 
//gtk_label_set_text(GTK_LABEL(label),gchar); 
// button event registering function - void button_clicked(GtkWidget *widget,gpointer data)
// contect button to register - g_signal_connect(button,"clicked",G_CALLBACK(function),NULL);

GtkWidget *k, *path, *name, *texttype, *imagetype, *soundtype;
int args;

int remove_char(char *s, int pos)
{
  int length = strlen(s);
  
  if (pos >= length) return false;
  
  for (int i = pos; i < length; i++)
    s[i] = s[i + 1];
  
  return true;
}

static void destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

void additem(GtkWidget *item, int x, int y) {
	gtk_fixed_put (GTK_FIXED (k), item,x,y);
}

void selectfile() {
	GtkWidget       *fc_dialog;
	GtkFileChooser  *fc;
	char            *filename;

	fc_dialog = gtk_file_chooser_dialog_new("Choose File", NULL, 		GTK_FILE_CHOOSER_ACTION_OPEN, 	"Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);

	gtk_widget_show(fc_dialog);

	if (gtk_dialog_run(GTK_DIALOG(fc_dialog)) == GTK_RESPONSE_ACCEPT){
     		fc = GTK_FILE_CHOOSER(fc_dialog);
     		filename = gtk_file_chooser_get_filename(fc);
     		gtk_entry_set_text(GTK_ENTRY(path),filename);
     		g_free (filename);
     		gtk_widget_destroy(fc_dialog);}
	else {
     		gtk_widget_destroy(fc_dialog);
     	}
}

void filebutton_clicked(GtkWidget *widget,gpointer data) {
	selectfile();
}

void makebutton_clicked(GtkWidget *widget,gpointer data) {
	//todo
	if (fopen(gtk_entry_get_text(GTK_ENTRY(path)),"r") == NULL) {
		g_print("Invalid path!\n");
	}
	else {

		//check if path is not null
		if (strlen(gtk_entry_get_text(GTK_ENTRY(name))) == 0) return;
		int namelen = strlen(gtk_entry_get_text(GTK_ENTRY(name)));

		//checks for valid path
		char namepath[4096] = "";
		strcpy(namepath, gtk_entry_get_text(GTK_ENTRY(name)));

		for (int i = namelen; gtk_entry_get_text(GTK_ENTRY(name))[i] != '/'; i--) {
			remove_char(namepath, i);
		}
		int pathlen = strlen(namepath);
		if (opendir(namepath) == null) return;

		printf("valid path!\n");

		//save file
		int type = 0;
		//type 0 - image
		//type 1 - audio/video
		//type 2 - other

		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(imagetype)) == 1) type = 0;
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(soundtype)) == 1) type = 1;
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(texttype)) == 1) type = 2;

		char shortcutpath[5100] = "";
		strcpy(shortcutpath, gtk_entry_get_text(GTK_ENTRY(name)));
		if (!args == 3) strcat(shortcutpath, ".lnk");
		if (args == 3) remove(shortcutpath);

		FILE *shortcut = fopen(shortcutpath,"w");

		fprintf(shortcut, "[shortcut]\npath=%s\ntype=%d",gtk_entry_get_text(GTK_ENTRY(path)),type);
		fclose(shortcut);

		//quit app
		gtk_main_quit();

		GtkWidget *dialog;
		GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
 		dialog = gtk_message_dialog_new (NULL,
                                  flags,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_OK,
								  "Succsesfully made shortcut!");
 		gtk_dialog_run (GTK_DIALOG (dialog));
 		gtk_widget_destroy (dialog);
	}
 }

void selectname_clicked(GtkWidget *widget,gpointer data) {
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	gint res;

	//make dialog
	dialog = gtk_file_chooser_dialog_new ("Shortcut Name",
                                      NULL,
                                      action,
                                      "Cancel",
                                      GTK_RESPONSE_CANCEL,
                                      "Save",
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);
	chooser = GTK_FILE_CHOOSER (dialog);
	gtk_file_chooser_set_do_overwrite_confirmation (chooser, FALSE);
	res = gtk_dialog_run (GTK_DIALOG (dialog));

	//check if user pressed "Save"
	if (res == GTK_RESPONSE_ACCEPT)
  	{
    	char *filename;
    	filename = gtk_file_chooser_get_filename (chooser);

		gtk_entry_set_text(GTK_ENTRY(name), filename);

		g_free(filename);
  	}

	gtk_widget_destroy (dialog);
}

void quitbutton_clicked(GtkWidget *widget,gpointer data) {
	gtk_main_quit();
}


int main(int argc, char *argv[])
{

	args = argc;
	int makebuttonx = 200;

	gtk_init(&argc, &argv);

	//make feilds
	path = gtk_entry_new();
	name = gtk_entry_new();

	//make radio buttons
	imagetype = gtk_radio_button_new_with_label(NULL,"Image");
	soundtype = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(imagetype), "Video/Audio");
	texttype = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(imagetype), "Other");

	gchar *title = "Linux Cuts";
	gchar *makebuttontext = "Create Shortcut";

	if (argc == 2) {
		if (fopen(argv[1], "r")) {
			printf("opening shortcut...\n");
			FILE *file = fopen(argv[1], "r");
			char line[5100] = "";
			char value[5100] = "";
			char fpath[5100] = "";
			char type[2] = "";

			while (fgets(line, 5100, file) != NULL) {
				char substr[5100] = "";
				if (strcmp(strncpy(substr, &line[0], 5),"path=") == 0) {
					strncpy(fpath, &line[strlen(substr)], strlen(line));
					
					fpath[strcspn(fpath, "\n")] = 0;

				}

				if (strcmp(strncpy(substr, &line[0], 5),"type=") == 0) {
					strncpy(type, &line[strlen(substr)], strlen(line));
					
					type[strcspn(type, "\n")] = 0;

				}
				
			}
			printf("path: %s\ntype: %s", fpath, type);

			if (strcmp(type, "2") == 0) {
					char cmd[9] = "gedit \"";
					strcat(cmd, fpath);
					strcat(cmd, "\"");
					printf("path: %s", fpath);
					printf("cmd: %s", cmd);
					system(cmd);
			}


			if (strcmp(type, "1") == 0) {
					char cmd[13] = "xdg-open \"";
					strcat(cmd, fpath);
					strcat(cmd, "\"");
					printf("path: %s", fpath);
					printf("cmd: %s", cmd);
					system(cmd);
			}


			if (strcmp(type, "0") == 0) {
					char cmd[9] = "eog \"";
					strcat(cmd, fpath);
					strcat(cmd, "\"");
					printf("path: %s", fpath);
					printf("cmd: %s", cmd);
					system(cmd);
			}

			fclose(file);
			return 0;
		}
		return EXIT_FAILURE;
	}


	//edit shortcut
	if (argc == 3) {

		if (fopen(argv[1], "r")) {

			printf("editing shortcut...\n");

			title = "Edit Shortcut";
			makebuttontext = "Save";

			//open shortcut file and create vars
			FILE *file = fopen(argv[1], "r");
			char line[5100] = "";
			char value[5100] = "";
			char fpath[5100] = "";
			char type[2] = "";

			//loop thr file
			while (fgets(line, 5100, file) != NULL) {

				//get path
				char substr[5100] = "";
				if (strcmp(strncpy(substr, &line[0], 5),"path=") == 0) {
					strncpy(fpath, &line[strlen(substr)], strlen(line));
					
					fpath[strcspn(fpath, "\n")] = 0;

				}

				//get type
				if (strcmp(strncpy(substr, &line[0], 5),"type=") == 0) {
					strncpy(type, &line[strlen(substr)], strlen(line));
					
					type[strcspn(type, "\n")] = 0;

				}
				
			}

			printf("path: %s\ntype: %s\n", fpath, type);

			gtk_entry_set_text(GTK_ENTRY(path), fpath);
			gtk_entry_set_text(GTK_ENTRY(name), argv[1]);

			if (strcmp(type, "0") == 0) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(imagetype), true);
			if (strcmp(type, "1") == 0) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(soundtype), true);
			if (strcmp(type, "2") == 0) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(texttype), true);

			makebuttonx = 270;

			//close file
			fclose(file);

		}
	}
	
	//make window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), title);
	g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

	k= gtk_fixed_new();
    	gtk_container_add(GTK_CONTAINER(window), k);
    	
    	//name field
    GtkWidget *namelabel, *pathlabel, *openfile, *make, *cancel, *savename, *typelabel;

	namelabel = gtk_label_new("Name:");
	gtk_entry_set_placeholder_text(GTK_ENTRY(name),"shortcut name");
	
	//path field
	pathlabel = gtk_label_new("Path:");
	gtk_entry_set_placeholder_text(GTK_ENTRY(path),"target path");
	
	//open file button
	openfile = gtk_button_new_with_label("📁");
	g_signal_connect(openfile,"clicked",G_CALLBACK(filebutton_clicked),NULL);

	savename = gtk_button_new_with_label("📂");
	g_signal_connect(savename,"clicked",G_CALLBACK(selectname_clicked),NULL);
	
	cancel = gtk_button_new_with_label("Cancel");
	g_signal_connect(cancel,"clicked",G_CALLBACK(quitbutton_clicked),NULL);
	
	make = gtk_button_new_with_label(makebuttontext);
	g_signal_connect(make,"clicked",G_CALLBACK(makebutton_clicked),NULL);

	//file type
	typelabel = gtk_label_new("File type:");
    	
    	//add items to GUI
    	additem(namelabel, 25, 33);
    	additem(name, 85,25);
    	additem(pathlabel, 25, 80);
    	additem(path, 85, 75);
    	additem(openfile, 275, 75);
    	additem(cancel, 15, 210);
    	additem(make, makebuttonx, 210);
		additem(savename, 275, 25);
		additem(typelabel,25,125);
		additem(imagetype, 25,155);
		additem(soundtype, 100, 155);
		additem(texttype, 215, 155);
  
	//set window size & show window
    	gtk_widget_set_size_request(GTK_WIDGET(window),350,260);
	gtk_widget_show_all(GTK_WIDGET(window));
	
	
	

gtk_main();
	return 0;
}
 
