#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtGui/QFont>
#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <vector>
#include "hotelsystem.h"

class HotelMainWindow : public QMainWindow
{
public:
    HotelMainWindow()
        : currentGuestIndex(-1)
    {
        setWindowTitle("Hotel Reservation System");
        resize(1400, 900);

        hotel = new HotelSystem();

        stack = new QStackedWidget(this);
        setCentralWidget(stack);

        buildStyles();
        buildHomePage();
        buildGuestRegisterPage();
        buildGuestLoginPage();
        buildAdminLoginPage();
        buildGuestDashboard();
        buildAdminDashboard();

        stack->setCurrentWidget(homePage);
    }

    ~HotelMainWindow()
    {
        delete hotel;
    }

private:
    QString buildSignature() const
    {
        return "BUILD-2026-05-07-B";
    }

    QString executablePathText() const
    {
        return QCoreApplication::applicationFilePath();
    }

    HotelSystem* hotel;
    int currentGuestIndex;

    QStackedWidget* stack;

    QWidget* homePage;
    QWidget* guestRegisterPage;
    QWidget* guestLoginPage;
    QWidget* adminLoginPage;
    QWidget* guestDashboardPage;
    QWidget* adminDashboardPage;

    QLabel* guestRegisterStatus;
    QLabel* guestLoginStatus;
    QLabel* adminLoginStatus;
    QLabel* guestDashboardStatus;
    QLabel* adminDashboardStatus;

    QPlainTextEdit* guestRegisterWorkspace;
    QPlainTextEdit* guestLoginWorkspace;
    QPlainTextEdit* adminLoginWorkspace;
    QPlainTextEdit* guestWorkspace;
    QPlainTextEdit* adminWorkspace;

    QListWidget* guestMenu;
    QListWidget* adminMenu;

    std::vector<QLineEdit*> guestRegisterFields;
    std::vector<QLineEdit*> guestLoginFields;
    std::vector<QLineEdit*> adminLoginFields;
    std::vector<QLabel*> guestFormLabels;
    std::vector<QLineEdit*> guestFormFields;
    std::vector<QComboBox*> guestFormCombos;
    std::vector<QStackedWidget*> guestFormInputs;
    std::vector<QLabel*> adminFormLabels;
    std::vector<QLineEdit*> adminFormFields;
    std::vector<QComboBox*> adminFormCombos;
    std::vector<QStackedWidget*> adminFormInputs;

    QPushButton* guestActionButton;
    QPushButton* adminActionButton;

    void buildStyles()
    {
        QFont titleFont("Segoe UI Semibold", 19);
        QFont subtitleFont("Segoe UI", 10);
        QFont sectionFont("Segoe UI Semibold", 11);
        QFont bodyFont("Segoe UI", 10);
        QFont monoFont("Consolas", 10);

        setFont(bodyFont);
        setStyleSheet(
            "QMainWindow, QWidget { background: #f3f6fb; color: #1f2937; }"
            "QFrame#heroCard { background: #ffffff; border: 1px solid #d5deea; border-radius: 18px; }"
            "QLabel#heroTitle { color: #123b6a; font: 700 28px 'Segoe UI'; background: transparent; }"
            "QLabel#heroSubtitle { color: #516174; font: 10pt 'Segoe UI'; background: transparent; }"
            "QGroupBox { background: white; border: 1px solid #d5deea; border-radius: 14px; margin-top: 14px; font: 600 11pt 'Segoe UI'; }"
            "QGroupBox::title { subcontrol-origin: margin; left: 14px; padding: 0 6px; color: #123b6a; }"
            "QPushButton { background: #123b6a; color: white; border: none; border-radius: 10px; padding: 10px 16px; font: 600 10pt 'Segoe UI'; }"
            "QPushButton:hover { background: #18497f; }"
            "QPushButton#secondary { background: white; color: #123b6a; border: 1px solid #c8d6e5; }"
            "QPushButton#secondary:hover { background: #f7fafd; }"
            "QLineEdit { background: #f9fbfd; border: 1px solid #ccd6e3; border-radius: 8px; padding: 8px 10px; }"
            "QLineEdit:focus { border: 1px solid #123b6a; background: white; }"
            "QListWidget { background: #fbfdff; border: 1px solid #d5deea; border-radius: 10px; padding: 6px; }"
            "QListWidget::item { padding: 10px; border-radius: 8px; }"
            "QListWidget::item:selected { background: #123b6a; color: white; }"
            "QPlainTextEdit { background: #fcfdff; border: 1px solid #d5deea; border-radius: 10px; padding: 10px; font: 10pt 'Consolas'; }"
            "QLabel#statusOk { color: #0f766e; font: 600 10pt 'Segoe UI'; }"
            "QLabel#statusWarn { color: #b45309; font: 600 10pt 'Segoe UI'; }"
        );

        Q_UNUSED(titleFont);
        Q_UNUSED(subtitleFont);
        Q_UNUSED(sectionFont);
        Q_UNUSED(monoFont);
    }

    QWidget* buildPageShell(const QString& title, const QString& subtitle, QLabel** statusOut, QWidget* body)
    {
        QWidget* page = new QWidget();
        QVBoxLayout* root = new QVBoxLayout(page);
        root->setContentsMargins(24, 24, 24, 24);
        root->setSpacing(18);

        QFrame* hero = new QFrame();
        hero->setObjectName("heroCard");
        QVBoxLayout* heroLayout = new QVBoxLayout(hero);
        heroLayout->setContentsMargins(28, 24, 28, 24);
        heroLayout->setSpacing(6);

        QLabel* titleLabel = new QLabel(title);
        titleLabel->setObjectName("heroTitle");
        QLabel* subtitleLabel = new QLabel(subtitle);
        subtitleLabel->setObjectName("heroSubtitle");
        subtitleLabel->setWordWrap(true);

        QLabel* statusLabel = new QLabel("Ready.");
        statusLabel->setObjectName("heroSubtitle");
        statusLabel->setWordWrap(true);

        heroLayout->addWidget(titleLabel);
        heroLayout->addWidget(subtitleLabel);
        heroLayout->addSpacing(6);
        heroLayout->addWidget(statusLabel);

        root->addWidget(hero);
        root->addWidget(body, 1);

        *statusOut = statusLabel;
        return page;
    }

    QGroupBox* createWorkspaceBox(const QString& title, QPlainTextEdit** output)
    {
        QGroupBox* box = new QGroupBox(title);
        QVBoxLayout* layout = new QVBoxLayout(box);
        *output = new QPlainTextEdit();
        (*output)->setReadOnly(true);
        layout->addWidget(*output);
        return box;
    }

    QGroupBox* createFormBox(const QString& title, const QStringList& labels, std::vector<QLineEdit*>& fields, QVBoxLayout** outerLayoutOut = 0)
    {
        QGroupBox* box = new QGroupBox(title);
        QVBoxLayout* outer = new QVBoxLayout(box);
        QFormLayout* form = new QFormLayout();
        form->setLabelAlignment(Qt::AlignLeft);
        form->setFormAlignment(Qt::AlignTop);
        form->setVerticalSpacing(12);
        form->setHorizontalSpacing(16);

        fields.clear();
        for (int i = 0; i < labels.size(); ++i)
        {
            QLineEdit* edit = new QLineEdit();
            form->addRow(labels[i], edit);
            fields.push_back(edit);
        }
        outer->addLayout(form);
        if (outerLayoutOut)
            *outerLayoutOut = outer;
        return box;
    }

    void buildHomePage()
    {
        QWidget* body = new QWidget();
        QHBoxLayout* bodyLayout = new QHBoxLayout(body);
        bodyLayout->setSpacing(18);

        QGroupBox* introBox = new QGroupBox("Welcome");
        QVBoxLayout* introLayout = new QVBoxLayout(introBox);
        QLabel* intro = new QLabel(
            "Guest Register creates a guest account.\n"
            "Guest Login login your account.\n"
            "Admin Login login admin account.\n"
        );
        intro->setWordWrap(true);
        introLayout->addWidget(intro);
        introLayout->addStretch();

        QGroupBox* actionBox = new QGroupBox("Start Here");
        QVBoxLayout* actionLayout = new QVBoxLayout(actionBox);
        QPushButton* btnGuestRegister = new QPushButton("Guest Register");
        QPushButton* btnGuestLogin = new QPushButton("Guest Login");
        QPushButton* btnAdminLogin = new QPushButton("Admin Login");
        actionLayout->addWidget(btnGuestRegister);
        actionLayout->addWidget(btnGuestLogin);
        actionLayout->addWidget(btnAdminLogin);
        actionLayout->addStretch();

        bodyLayout->addWidget(introBox, 3);
        bodyLayout->addWidget(actionBox, 2);

        homePage = buildPageShell(
            "Hotel Reservation System",
            "Allow you to reserve Hotel",
            &guestLoginStatus,
            body
        );

        connect(btnGuestRegister, &QPushButton::clicked, this, [this]() {
            clearEdits(guestRegisterFields);
            setWorkspace(guestRegisterWorkspace, QString("Create a guest account."));
            setStatusLabel(guestRegisterStatus, "Fill in the guest registration form.");
            stack->setCurrentWidget(guestRegisterPage);
        });
        connect(btnGuestLogin, &QPushButton::clicked, this, [this]() {
            clearEdits(guestLoginFields);
            setWorkspace(guestLoginWorkspace, "Enter guest credentials and continue to the dashboard.");
            setStatusLabel(guestLoginStatus, "Fill in the guest login form.");
            stack->setCurrentWidget(guestLoginPage);
        });
        connect(btnAdminLogin, &QPushButton::clicked, this, [this]() {
            clearEdits(adminLoginFields);
            setWorkspace(adminLoginWorkspace, "Default admin credentials:\nUsername: admin\nPassword: 1234");
            setStatusLabel(adminLoginStatus, "Fill in the admin login form.");
            stack->setCurrentWidget(adminLoginPage);
        });

        stack->addWidget(homePage);
    }

    void buildGuestRegisterPage()
    {
        QWidget* body = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(body);
        layout->setSpacing(18);

        QVBoxLayout* formWrapper = 0;
        QGroupBox* formBox = createFormBox(
            "Guest Registration",
            QStringList() << "Username" << "Password" << "Full Name" << "Phone" << "CNIC" << "Address",
            guestRegisterFields,
            &formWrapper
        );
        guestRegisterFields[1]->setEchoMode(QLineEdit::Password);

        QPushButton* backButton = new QPushButton("Back");
        backButton->setObjectName("secondary");
        QPushButton* submitButton = new QPushButton("Create Guest Account");

        QHBoxLayout* actions = new QHBoxLayout();
        actions->addWidget(backButton);
        actions->addWidget(submitButton);
        formWrapper->addSpacing(8);
        formWrapper->addLayout(actions);

        QGroupBox* workspaceBox = createWorkspaceBox("Workspace", &guestRegisterWorkspace);

        layout->addWidget(formBox, 2);
        layout->addWidget(workspaceBox, 3);

        guestRegisterPage = buildPageShell(
            "Guest Registration",
            "Create a guest account ",
            &guestRegisterStatus,
            body
        );

        connect(backButton, &QPushButton::clicked, this, [this]() {
            stack->setCurrentWidget(homePage);
        });
        connect(submitButton, &QPushButton::clicked, this, [this]() {
            string message;
            bool ok = hotel->registerGuestGui(
                guestRegisterFields[0]->text().toStdString(),
                guestRegisterFields[1]->text().toStdString(),
                guestRegisterFields[2]->text().toStdString(),
                guestRegisterFields[3]->text().toStdString(),
                guestRegisterFields[4]->text().toStdString(),
                guestRegisterFields[5]->text().toStdString(),
                message
            );
            setStatusLabel(guestRegisterStatus, QString::fromStdString(message));
            setWorkspace(guestRegisterWorkspace, QString::fromStdString(message));
            showMessage(ok, "Guest Registration", QString::fromStdString(message));
            if (ok)
            {
                clearEdits(guestRegisterFields);
                stack->setCurrentWidget(homePage);
            }
        });

        stack->addWidget(guestRegisterPage);
    }

    void buildGuestLoginPage()
    {
        QWidget* body = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(body);
        layout->setSpacing(18);

        QVBoxLayout* formWrapper = 0;
        QGroupBox* formBox = createFormBox(
            "Guest Login",
            QStringList() << "Username" << "Password",
            guestLoginFields,
            &formWrapper
        );
        guestLoginFields[1]->setEchoMode(QLineEdit::Password);

        QPushButton* backButton = new QPushButton("Back");
        backButton->setObjectName("secondary");
        QPushButton* submitButton = new QPushButton("Login as Guest");

        QHBoxLayout* actions = new QHBoxLayout();
        actions->addWidget(backButton);
        actions->addWidget(submitButton);
        formWrapper->addSpacing(8);
        formWrapper->addLayout(actions);

        QGroupBox* workspaceBox = createWorkspaceBox("Workspace", &guestLoginWorkspace);

        layout->addWidget(formBox, 2);
        layout->addWidget(workspaceBox, 3);

        guestLoginPage = buildPageShell(
            "Guest Login",
            "Access reservations, payment details, and personal stay information.",
            &guestLoginStatus,
            body
        );

        connect(backButton, &QPushButton::clicked, this, [this]() {
            stack->setCurrentWidget(homePage);
        });
        connect(submitButton, &QPushButton::clicked, this, [this]() {
            string message;
            currentGuestIndex = hotel->loginGuestGui(
                guestLoginFields[0]->text().toStdString(),
                guestLoginFields[1]->text().toStdString(),
                message
            );
            setStatusLabel(guestLoginStatus, QString::fromStdString(message));
            setWorkspace(guestLoginWorkspace, QString::fromStdString(message));

            if (currentGuestIndex >= 0)
            {
                QMessageBox::information(this, "Guest Login", "Guest login successful.");
                clearEdits(guestLoginFields);
                guestMenu->setCurrentRow(0);
                refreshGuestDashboard();
                stack->setCurrentWidget(guestDashboardPage);
            }
            else
            {
                QMessageBox::warning(this, "Guest Login Failed", QString::fromStdString(message));
            }
        });

        stack->addWidget(guestLoginPage);
    }

    void buildAdminLoginPage()
    {
        QWidget* body = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(body);
        layout->setSpacing(18);

        QVBoxLayout* formWrapper = 0;
        QGroupBox* formBox = createFormBox(
            "Admin Login",
            QStringList() << "Username" << "Password",
            adminLoginFields,
            &formWrapper
        );
        adminLoginFields[1]->setEchoMode(QLineEdit::Password);

        QPushButton* backButton = new QPushButton("Back");
        backButton->setObjectName("secondary");
        QPushButton* submitButton = new QPushButton("Login as Admin");

        QHBoxLayout* actions = new QHBoxLayout();
        actions->addWidget(backButton);
        actions->addWidget(submitButton);
        formWrapper->addSpacing(8);
        formWrapper->addLayout(actions);

        QGroupBox* workspaceBox = createWorkspaceBox("Workspace", &adminLoginWorkspace);

        layout->addWidget(formBox, 2);
        layout->addWidget(workspaceBox, 3);

        adminLoginPage = buildPageShell(
            "Admin Login",
            "Open the hotel operations workspace for rooms, bookings, billing, records, and policies.",
            &adminLoginStatus,
            body
        );

        connect(backButton, &QPushButton::clicked, this, [this]() {
            stack->setCurrentWidget(homePage);
        });
        connect(submitButton, &QPushButton::clicked, this, [this]() {
            string message;
            bool ok = hotel->loginAdminGui(
                adminLoginFields[0]->text().toStdString(),
                adminLoginFields[1]->text().toStdString(),
                message
            );
            setStatusLabel(adminLoginStatus, QString::fromStdString(message));
            setWorkspace(adminLoginWorkspace, QString::fromStdString(message));

            if (ok)
            {
                QMessageBox::information(this, "Admin Login", "Admin login successful.");
                clearEdits(adminLoginFields);
                adminMenu->setCurrentRow(0);
                refreshAdminDashboard();
                stack->setCurrentWidget(adminDashboardPage);
            }
            else
            {
                QMessageBox::warning(this, "Admin Login Failed", QString::fromStdString(message));
            }
        });

        stack->addWidget(adminLoginPage);
    }

    void buildGuestDashboard()
    {
        QWidget* body = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(body);
        layout->setSpacing(18);

        QGroupBox* navBox = new QGroupBox("Guest Actions");
        QVBoxLayout* navLayout = new QVBoxLayout(navBox);
        guestMenu = new QListWidget();
        guestMenu->addItems(QStringList()
            << "View My Info"
            << "View Available Rooms"
            << "Book a Room"
            << "View My Bookings"
            << "View My Bills"
            << "Pay Bill"
            << "Update My Info"
            << "Hotel Policies");
        navLayout->addWidget(guestMenu);

        QGroupBox* formBox = new QGroupBox("Action Form");
        QVBoxLayout* formOuter = new QVBoxLayout(formBox);
        QFormLayout* formLayout = new QFormLayout();
        formLayout->setVerticalSpacing(12);
        formLayout->setHorizontalSpacing(16);

        for (int i = 0; i < 5; ++i)
        {
            QLabel* label = new QLabel();
            QLineEdit* edit = new QLineEdit();
            QComboBox* combo = new QComboBox();
            QStackedWidget* input = new QStackedWidget();
            input->addWidget(edit);
            input->addWidget(combo);
            guestFormLabels.push_back(label);
            guestFormFields.push_back(edit);
            guestFormCombos.push_back(combo);
            guestFormInputs.push_back(input);
            formLayout->addRow(label, input);
        }
        guestActionButton = new QPushButton("Run Action");
        QPushButton* guestLogoutButton = new QPushButton("Logout");
        guestLogoutButton->setObjectName("secondary");
        formOuter->addLayout(formLayout);
        formOuter->addSpacing(8);
        formOuter->addWidget(guestActionButton);
        formOuter->addWidget(guestLogoutButton);
        formOuter->addStretch();

        QGroupBox* workspaceBox = createWorkspaceBox("Workspace", &guestWorkspace);

        layout->addWidget(navBox, 2);
        layout->addWidget(formBox, 2);
        layout->addWidget(workspaceBox, 3);

        guestDashboardPage = buildPageShell(
            "Guest Dashboard",
            "Professional workspace for bookings, bills, profile updates, and hotel policy review.",
            &guestDashboardStatus,
            body
        );

        connect(guestMenu, &QListWidget::currentRowChanged, this, [this](int) {
            configureGuestForm();
        });
        connect(guestFormCombos[0], &QComboBox::currentTextChanged, this, [this](const QString&) {
            populateGuestRoomNumbers();
        });
        connect(guestActionButton, &QPushButton::clicked, this, [this]() {
            runGuestAction();
        });
        connect(guestLogoutButton, &QPushButton::clicked, this, [this]() {
            currentGuestIndex = -1;
            stack->setCurrentWidget(homePage);
        });

        stack->addWidget(guestDashboardPage);
    }

    void buildAdminDashboard()
    {
        QWidget* body = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(body);
        layout->setSpacing(18);

        QGroupBox* navBox = new QGroupBox("Admin Actions");
        QVBoxLayout* navLayout = new QVBoxLayout(navBox);
        adminMenu = new QListWidget();
        adminMenu->addItems(QStringList()
            << "View All Guests"
            << "Search Guest"
            << "Delete Guest"
            << "View Rooms"
            << "Add Single Room"
            << "Add Double Room"
            << "Add Suite Room"
            << "View Bookings"
            << "Check In Booking"
            << "Check Out Booking"
            << "Cancel Booking"
            << "View Bills"
            << "Apply Discount"
            << "Detailed Bill"
            << "View Rules"
            << "Add Rule"
            << "Update Rule"
            << "View Records"
            << "Generate Report"
            << "Save Records File"
            << "Load Records File"
            << "Admin Info"
            << "Change Password"
            << "Hotel Policies");
        navLayout->addWidget(adminMenu);

        QGroupBox* formBox = new QGroupBox("Action Form");
        QVBoxLayout* formOuter = new QVBoxLayout(formBox);
        QFormLayout* formLayout = new QFormLayout();
        formLayout->setVerticalSpacing(12);
        formLayout->setHorizontalSpacing(16);

        for (int i = 0; i < 5; ++i)
        {
            QLabel* label = new QLabel();
            QLineEdit* edit = new QLineEdit();
            QComboBox* combo = new QComboBox();
            QStackedWidget* input = new QStackedWidget();
            input->addWidget(edit);
            input->addWidget(combo);
            adminFormLabels.push_back(label);
            adminFormFields.push_back(edit);
            adminFormCombos.push_back(combo);
            adminFormInputs.push_back(input);
            formLayout->addRow(label, input);
        }
        adminActionButton = new QPushButton("Run Action");
        QPushButton* adminLogoutButton = new QPushButton("Logout");
        adminLogoutButton->setObjectName("secondary");
        formOuter->addLayout(formLayout);
        formOuter->addSpacing(8);
        formOuter->addWidget(adminActionButton);
        formOuter->addWidget(adminLogoutButton);
        formOuter->addStretch();

        QGroupBox* workspaceBox = createWorkspaceBox("Workspace", &adminWorkspace);

        layout->addWidget(navBox, 2);
        layout->addWidget(formBox, 2);
        layout->addWidget(workspaceBox, 3);

        adminDashboardPage = buildPageShell(
            "Admin Dashboard",
            "Professional workspace for guest operations, room inventory, booking control, billing, rules, and records.",
            &adminDashboardStatus,
            body
        );

        connect(adminMenu, &QListWidget::currentRowChanged, this, [this](int) {
            configureAdminForm();
        });
        connect(adminFormCombos[0], &QComboBox::currentTextChanged, this, [this](const QString&) {
            syncAdminRuleFields();
        });
        connect(adminActionButton, &QPushButton::clicked, this, [this]() {
            runAdminAction();
        });
        connect(adminLogoutButton, &QPushButton::clicked, this, [this]() {
            hotel->logoutAdminGui();
            stack->setCurrentWidget(homePage);
        });

        stack->addWidget(adminDashboardPage);
    }

    void clearEdits(std::vector<QLineEdit*>& fields)
    {
        for (size_t i = 0; i < fields.size(); ++i)
            fields[i]->clear();
    }

    void setWorkspace(QPlainTextEdit* workspace, const QString& text)
    {
        workspace->setPlainText(text);
    }

    void setStatusLabel(QLabel* label, const QString& text)
    {
        label->setText(text);
    }

    void showMessage(bool ok, const QString& title, const QString& message)
    {
        if (ok)
            QMessageBox::information(this, title, message);
        else
            QMessageBox::warning(this, title, message);
    }

    void hideGuestForm()
    {
        for (size_t i = 0; i < guestFormLabels.size(); ++i)
        {
            guestFormLabels[i]->hide();
            guestFormInputs[i]->hide();
            guestFormFields[i]->clear();
            guestFormFields[i]->setEchoMode(QLineEdit::Normal);
            guestFormCombos[i]->clear();
            guestFormInputs[i]->setCurrentWidget(guestFormFields[i]);
        }
    }

    void hideAdminForm()
    {
        for (size_t i = 0; i < adminFormLabels.size(); ++i)
        {
            adminFormLabels[i]->hide();
            adminFormInputs[i]->hide();
            adminFormFields[i]->clear();
            adminFormFields[i]->setEchoMode(QLineEdit::Normal);
            adminFormCombos[i]->clear();
            adminFormInputs[i]->setCurrentWidget(adminFormFields[i]);
        }
    }

    void showGuestField(int index, const QString& label, bool password = false)
    {
        guestFormLabels[index]->setText(label);
        guestFormFields[index]->setEchoMode(password ? QLineEdit::Password : QLineEdit::Normal);
        guestFormInputs[index]->setCurrentWidget(guestFormFields[index]);
        guestFormLabels[index]->show();
        guestFormInputs[index]->show();
    }

    void showGuestDropdown(int index, const QString& label, const QStringList& options)
    {
        guestFormLabels[index]->setText(label);
        guestFormCombos[index]->clear();
        guestFormCombos[index]->addItems(options);
        guestFormInputs[index]->setCurrentWidget(guestFormCombos[index]);
        guestFormLabels[index]->show();
        guestFormInputs[index]->show();
    }

    void showAdminDropdown(int index, const QString& label, const QStringList& options)
    {
        adminFormLabels[index]->setText(label);
        adminFormCombos[index]->clear();
        adminFormCombos[index]->addItems(options);
        adminFormInputs[index]->setCurrentWidget(adminFormCombos[index]);
        adminFormLabels[index]->show();
        adminFormInputs[index]->show();
    }

    void showAdminField(int index, const QString& label, bool password = false)
    {
        adminFormLabels[index]->setText(label);
        adminFormFields[index]->setEchoMode(password ? QLineEdit::Password : QLineEdit::Normal);
        adminFormInputs[index]->setCurrentWidget(adminFormFields[index]);
        adminFormLabels[index]->show();
        adminFormInputs[index]->show();
    }

    QString guestFieldText(int index) const
    {
        if (guestFormInputs[index]->currentWidget() == guestFormCombos[index])
            return guestFormCombos[index]->currentText();
        return guestFormFields[index]->text();
    }

    QString adminFieldText(int index) const
    {
        if (adminFormInputs[index]->currentWidget() == adminFormCombos[index])
            return adminFormCombos[index]->currentText();
        return adminFormFields[index]->text();
    }

    QStringList idOptions(const std::vector<int>& ids, const QString& emptyText) const
    {
        QStringList options;
        if (ids.empty())
            options << emptyText;
        else
            for (size_t i = 0; i < ids.size(); ++i)
                options << QString::number(ids[i]);
        return options;
    }

    void populateGuestRoomNumbers()
    {
        if (guestMenu->currentRow() != 2)
            return;

        QString roomType = guestFieldText(0);
        showGuestDropdown(1, "Room Number", idOptions(hotel->getAvailableRoomNumbers(roomType.toStdString()), "No rooms available"));
    }

    void populateGuestBillOptions()
    {
        showGuestDropdown(0, "Bill ID", idOptions(hotel->getGuestBillIds(currentGuestIndex, true), "No unpaid bills"));
    }

    void populateAdminGuestOptions(int index, const QString& label)
    {
        showAdminDropdown(index, label, idOptions(hotel->getGuestIds(), "No guests"));
    }

    void populateAdminBookingOptions(int index, const QString& label)
    {
        showAdminDropdown(index, label, idOptions(hotel->getBookingIds(), "No bookings"));
    }

    void populateAdminBillOptions(int index, const QString& label)
    {
        showAdminDropdown(index, label, idOptions(hotel->getBillIds(), "No bills"));
    }

    void populateAdminRuleOptions()
    {
        showAdminDropdown(0, "Rule ID", idOptions(hotel->getRuleIds(), "No rules"));
    }

    void syncGuestProfileFields()
    {
        string name;
        string phone;
        string address;
        if (hotel->getGuestProfileValues(currentGuestIndex, name, phone, address))
        {
            guestFormFields[0]->setText(QString::fromStdString(name));
            guestFormFields[1]->setText(QString::fromStdString(phone));
            guestFormFields[2]->setText(QString::fromStdString(address));
        }
    }

    void syncAdminRuleFields()
    {
        if (adminMenu->currentRow() != 16)
            return;

        bool ok = false;
        int ruleId = adminFieldText(0).toInt(&ok);
        string title;
        string description;
        if (ok && hotel->getRuleValues(ruleId, title, description))
        {
            adminFormFields[1]->setText(QString::fromStdString(title));
            adminFormFields[2]->setText(QString::fromStdString(description));
        }
        else
        {
            adminFormFields[1]->clear();
            adminFormFields[2]->clear();
        }
    }

    void configureGuestForm()
    {
        hideGuestForm();
        int row = guestMenu->currentRow();

        switch (row)
        {
        case 0:
            guestActionButton->setText("Refresh Info");
            setWorkspace(guestWorkspace, QString::fromStdString(hotel->getGuestInfoText(currentGuestIndex)));
            setStatusLabel(guestDashboardStatus, "Viewing guest profile.");
            break;
        case 1:
            guestActionButton->setText("Refresh Rooms");
            setWorkspace(guestWorkspace, QString::fromStdString(hotel->getAvailableRoomsText()));
            setStatusLabel(guestDashboardStatus, "Showing available rooms.");
            break;
        case 2:
            guestActionButton->setText("Book Room");
            showGuestDropdown(0, "Room Type", QStringList() << "Single" << "Double" << "Suite");
            populateGuestRoomNumbers();
            showGuestField(2, "Total Days");
            setWorkspace(guestWorkspace, QString::fromStdString(hotel->getAvailableRoomsText()));
            setStatusLabel(guestDashboardStatus, "Select a room and enter total days. Check-in and check-out will be filled automatically.");
            break;
        case 3:
            guestActionButton->setText("Refresh Bookings");
            setWorkspace(guestWorkspace, QString::fromStdString(hotel->getGuestBookingsText(currentGuestIndex)));
            setStatusLabel(guestDashboardStatus, "Showing guest bookings.");
            break;
        case 4:
            guestActionButton->setText("Refresh Bills");
            setWorkspace(guestWorkspace, QString::fromStdString(hotel->getGuestBillsText(currentGuestIndex)));
            setStatusLabel(guestDashboardStatus, "Showing guest bills.");
            break;
        case 5:
            guestActionButton->setText("Pay Bill");
            populateGuestBillOptions();
            showGuestDropdown(1, "Payment Method", QStringList() << "1 - Cash" << "2 - Card" << "3 - Online");
            setWorkspace(guestWorkspace, QString::fromStdString(hotel->getGuestBillsText(currentGuestIndex)));
            setStatusLabel(guestDashboardStatus, "Choose an unpaid bill and payment method.");
            break;
        case 6:
            guestActionButton->setText("Update Info");
            showGuestField(0, "New Name");
            showGuestField(1, "New Phone");
            showGuestField(2, "New Address");
            syncGuestProfileFields();
            setWorkspace(guestWorkspace, QString::fromStdString(hotel->getGuestInfoText(currentGuestIndex)));
            setStatusLabel(guestDashboardStatus, "Update your guest information. Change any field you want and leave the rest as-is.");
            break;
        case 7:
            guestActionButton->setText("Refresh Policies");
            setWorkspace(guestWorkspace, QString::fromStdString(hotel->getPoliciesText()));
            setStatusLabel(guestDashboardStatus, "Showing hotel policies.");
            break;
        default:
            break;
        }
    }

    void configureAdminForm()
    {
        hideAdminForm();
        int row = adminMenu->currentRow();

        switch (row)
        {
        case 0:
            adminActionButton->setText("Refresh Guests");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllGuestsText()));
            setStatusLabel(adminDashboardStatus, "Showing all guests.");
            break;
        case 1:
            adminActionButton->setText("Search Guest");
            populateAdminGuestOptions(0, "Guest ID");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllGuestsText()));
            break;
        case 2:
            adminActionButton->setText("Delete Guest");
            populateAdminGuestOptions(0, "Guest ID");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllGuestsText()));
            break;
        case 3:
            adminActionButton->setText("Refresh Rooms");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllRoomsText()));
            break;
        case 4:
            adminActionButton->setText("Add Single Room");
            showAdminField(0, "Room Number");
            showAdminField(1, "Price");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllRoomsText()));
            break;
        case 5:
            adminActionButton->setText("Add Double Room");
            showAdminField(0, "Room Number");
            showAdminField(1, "Price");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllRoomsText()));
            break;
        case 6:
            adminActionButton->setText("Add Suite Room");
            showAdminField(0, "Room Number");
            showAdminField(1, "Price");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllRoomsText()));
            break;
        case 7:
            adminActionButton->setText("Refresh Bookings");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllBookingsText()));
            break;
        case 8:
            adminActionButton->setText("Check In");
            populateAdminBookingOptions(0, "Booking ID");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllBookingsText()));
            break;
        case 9:
            adminActionButton->setText("Check Out");
            populateAdminBookingOptions(0, "Booking ID");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllBookingsText()));
            break;
        case 10:
            adminActionButton->setText("Cancel Booking");
            populateAdminBookingOptions(0, "Booking ID");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllBookingsText()));
            break;
        case 11:
            adminActionButton->setText("Refresh Bills");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllBillsText()));
            break;
        case 12:
            adminActionButton->setText("Apply Discount");
            populateAdminBillOptions(0, "Bill ID");
            showAdminField(1, "Discount %");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllBillsText()));
            break;
        case 13:
            adminActionButton->setText("Show Detailed Bill");
            populateAdminBillOptions(0, "Bill ID");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllBillsText()));
            break;
        case 14:
            adminActionButton->setText("Refresh Rules");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getRulesText()));
            break;
        case 15:
            adminActionButton->setText("Add Rule");
            showAdminField(1, "Title");
            showAdminField(2, "Description");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getRulesText()));
            setStatusLabel(adminDashboardStatus, QString("Next Rule ID will be auto-generated: %1").arg(hotel->getNextRuleId()));
            break;
        case 16:
            adminActionButton->setText("Update Rule");
            populateAdminRuleOptions();
            showAdminField(1, "Title");
            showAdminField(2, "Description");
            syncAdminRuleFields();
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getRulesText()));
            break;
        case 17:
            adminActionButton->setText("Refresh Records");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getRecordsText()));
            break;
        case 18:
            adminActionButton->setText("Generate Report");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getRecordReportText()));
            break;
        case 19:
            adminActionButton->setText("Save Records File");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getRecordReportText()));
            break;
        case 20:
            adminActionButton->setText("Load Records File");
            setWorkspace(adminWorkspace, "Click the action button to load saved record data.");
            break;
        case 21:
            adminActionButton->setText("Refresh Admin Info");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAdminInfoText()));
            break;
        case 22:
            adminActionButton->setText("Change Password");
            showAdminField(0, "Old Password", true);
            showAdminField(1, "New Password", true);
            showAdminField(2, "Confirm Password", true);
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAdminInfoText()));
            break;
        case 23:
            adminActionButton->setText("Refresh Policies");
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getPoliciesText()));
            break;
        default:
            break;
        }
    }

    void refreshGuestDashboard()
    {
        configureGuestForm();
    }

    void refreshAdminDashboard()
    {
        configureAdminForm();
    }

    void runGuestAction()
    {
        string message;
        bool ok = false;
        int row = guestMenu->currentRow();

        switch (row)
        {
        case 0:
            setWorkspace(guestWorkspace, QString::fromStdString(hotel->getGuestInfoText(currentGuestIndex)));
            break;
        case 1:
            setWorkspace(guestWorkspace, QString::fromStdString(hotel->getAvailableRoomsText()));
            break;
        case 2:
            ok = hotel->bookRoomGui(
                currentGuestIndex,
                guestFieldText(0).toStdString(),
                guestFieldText(1).toInt(),
                "",
                "",
                guestFormFields[2]->text().toInt(),
                message
            );
            setStatusLabel(guestDashboardStatus, QString::fromStdString(message));
            setWorkspace(guestWorkspace,
                QString::fromStdString(hotel->getAvailableRoomsText()) + "\n\n" +
                QString::fromStdString(hotel->getGuestBookingsText(currentGuestIndex)));
            if (ok) clearEdits(guestFormFields);
            break;
        case 3:
            setWorkspace(guestWorkspace, QString::fromStdString(hotel->getGuestBookingsText(currentGuestIndex)));
            break;
        case 4:
            setWorkspace(guestWorkspace, QString::fromStdString(hotel->getGuestBillsText(currentGuestIndex)));
            break;
        case 5:
            ok = hotel->payGuestBillGui(
                currentGuestIndex,
                guestFieldText(0).toInt(),
                guestFieldText(1).left(1).toInt(),
                message
            );
            setStatusLabel(guestDashboardStatus, QString::fromStdString(message));
            setWorkspace(guestWorkspace, QString::fromStdString(hotel->getGuestBillsText(currentGuestIndex)));
            if (ok) clearEdits(guestFormFields);
            break;
        case 6:
            ok = hotel->updateGuestInfoGui(
                currentGuestIndex,
                guestFormFields[0]->text().toStdString(),
                guestFormFields[1]->text().toStdString(),
                guestFormFields[2]->text().toStdString(),
                message
            );
            setStatusLabel(guestDashboardStatus, QString::fromStdString(message));
            setWorkspace(guestWorkspace, QString::fromStdString(hotel->getGuestInfoText(currentGuestIndex)));
            if (ok) clearEdits(guestFormFields);
            break;
        case 7:
            setWorkspace(guestWorkspace, QString::fromStdString(hotel->getPoliciesText()));
            break;
        default:
            break;
        }

        if (ok)
            QMessageBox::information(this, "Guest Action", QString::fromStdString(message));
        else if (!message.empty())
            QMessageBox::warning(this, "Guest Action", QString::fromStdString(message));
    }

    void runAdminAction()
    {
        string message;
        bool ok = false;
        int row = adminMenu->currentRow();

        switch (row)
        {
        case 0:
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllGuestsText()));
            break;
        case 1:
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getGuestByIdText(adminFieldText(0).toInt())));
            setStatusLabel(adminDashboardStatus, "Guest search completed.");
            break;
        case 2:
            ok = hotel->deleteGuestGui(adminFieldText(0).toInt(), message);
            setStatusLabel(adminDashboardStatus, QString::fromStdString(message));
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllGuestsText()));
            if (ok) clearEdits(adminFormFields);
            break;
        case 3:
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllRoomsText()));
            break;
        case 4:
            ok = hotel->addRoomGui("Single", adminFormFields[0]->text().toInt(), adminFormFields[1]->text().toDouble(), message);
            setStatusLabel(adminDashboardStatus, QString::fromStdString(message));
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllRoomsText()));
            if (ok) clearEdits(adminFormFields);
            break;
        case 5:
            ok = hotel->addRoomGui("Double", adminFormFields[0]->text().toInt(), adminFormFields[1]->text().toDouble(), message);
            setStatusLabel(adminDashboardStatus, QString::fromStdString(message));
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllRoomsText()));
            if (ok) clearEdits(adminFormFields);
            break;
        case 6:
            ok = hotel->addRoomGui("Suite", adminFormFields[0]->text().toInt(), adminFormFields[1]->text().toDouble(), message);
            setStatusLabel(adminDashboardStatus, QString::fromStdString(message));
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllRoomsText()));
            if (ok) clearEdits(adminFormFields);
            break;
        case 7:
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllBookingsText()));
            break;
        case 8:
            ok = hotel->checkInBookingGui(adminFieldText(0).toInt(), message);
            setStatusLabel(adminDashboardStatus, QString::fromStdString(message));
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllBookingsText()));
            if (ok) clearEdits(adminFormFields);
            break;
        case 9:
            ok = hotel->checkOutBookingGui(adminFieldText(0).toInt(), message);
            setStatusLabel(adminDashboardStatus, QString::fromStdString(message));
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllBookingsText()));
            if (ok) clearEdits(adminFormFields);
            break;
        case 10:
            ok = hotel->cancelBookingGui(adminFieldText(0).toInt(), message);
            setStatusLabel(adminDashboardStatus, QString::fromStdString(message));
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllBookingsText()));
            if (ok) clearEdits(adminFormFields);
            break;
        case 11:
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllBillsText()));
            break;
        case 12:
            ok = hotel->applyDiscountGui(adminFieldText(0).toInt(), adminFormFields[1]->text().toDouble(), message);
            setStatusLabel(adminDashboardStatus, QString::fromStdString(message));
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAllBillsText()));
            if (ok) clearEdits(adminFormFields);
            break;
        case 13:
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getDetailedBillText(adminFieldText(0).toInt())));
            setStatusLabel(adminDashboardStatus, "Detailed bill loaded.");
            break;
        case 14:
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getRulesText()));
            break;
        case 15:
            ok = hotel->addRuleGui(
                adminFormFields[1]->text().toStdString(),
                adminFormFields[2]->text().toStdString(),
                message
            );
            setStatusLabel(adminDashboardStatus, QString::fromStdString(message));
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getRulesText()));
            if (ok) clearEdits(adminFormFields);
            break;
        case 16:
            ok = hotel->updateRuleGui(
                adminFieldText(0).toInt(),
                adminFormFields[1]->text().toStdString(),
                adminFormFields[2]->text().toStdString(),
                message
            );
            setStatusLabel(adminDashboardStatus, QString::fromStdString(message));
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getRulesText()));
            if (ok) clearEdits(adminFormFields);
            break;
        case 17:
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getRecordsText()));
            break;
        case 18:
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getRecordReportText()));
            break;
        case 19:
            ok = hotel->saveRecordsToFileGui(message);
            setStatusLabel(adminDashboardStatus, QString::fromStdString(message));
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getRecordReportText()));
            break;
        case 20:
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->loadRecordsFromFileGui(message)));
            setStatusLabel(adminDashboardStatus, QString::fromStdString(message));
            ok = true;
            break;
        case 21:
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAdminInfoText()));
            break;
        case 22:
            ok = hotel->changeAdminPasswordGui(
                adminFormFields[0]->text().toStdString(),
                adminFormFields[1]->text().toStdString(),
                adminFormFields[2]->text().toStdString(),
                message
            );
            setStatusLabel(adminDashboardStatus, QString::fromStdString(message));
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getAdminInfoText()));
            if (ok) clearEdits(adminFormFields);
            break;
        case 23:
            setWorkspace(adminWorkspace, QString::fromStdString(hotel->getPoliciesText()));
            break;
        default:
            break;
        }

        if (ok)
            QMessageBox::information(this, "Admin Action", QString::fromStdString(message));
        else if (!message.empty() && row != 0 && row != 3 && row != 7 && row != 11 && row != 14 && row != 17 && row != 18 && row != 21 && row != 23)
            QMessageBox::warning(this, "Admin Action", QString::fromStdString(message));
    }
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    HotelMainWindow window;
    window.show();
    return app.exec();
}
