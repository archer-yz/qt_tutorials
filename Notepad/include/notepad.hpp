/* cSpell:disable */
#ifndef NOTEPAD_A37DA5C2_9860_4984_A564_14FDE13F1584
#define NOTEPAD_A37DA5C2_9860_4984_A564_14FDE13F1584

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QTextEdit;
class QMenu;
class QAction;
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
	Q_OBJECT  // NOLINT

 public:
	explicit Notepad(QWidget* parent = nullptr);
	~Notepad();

 private:
	QTextEdit *text_edit;
	QMenu *file_menu;
	QMenu *edit_menu;
	QMenu *about_menu;

	QAction *new_action;
	QAction *open_action;
	QAction *save_action;
	QAction *saveas_action;
	QAction *print_action;
	QAction *exit_action;

	QAction *copy_action;
	QAction *cut_action;
	QAction *paste_action;
	QAction *undo_action;
	QAction *redo_action;
	QAction *font_action;

	QAction *bold_action;
	QAction *italic_action;
	QAction *underline_action;

	QAction *about_action;

	void create_menus();
	void create_actions();
	void create_toolbars();
	void create_connections();

	QString current_file;

private slots:
	void newDocument();
	void open();
	void save();
	void saveAs();
	void print();
	void selectFont();
	void setFontBold(bool bold);
	void setFontUnderline(bool underline);
	void setFontItalic(bool italic);
	void about();
};

#endif /* NOTEPAD_A37DA5C2_9860_4984_A564_14FDE13F1584 */
