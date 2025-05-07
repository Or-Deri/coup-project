#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QString>

#include "Game.hpp"
#include "Role/Governor.hpp"
#include "Role/Spy.hpp"
#include "Role/Baron.hpp"
#include "Role/General.hpp"
#include "Role/Judge.hpp"
#include "Role/Merchant.hpp"

enum class ActionType {
    Income,
    ForeignAid,
    Coup,
    Tax,
    Spy,
    Invest,
    Protect,
    Bribe,
    None
};

class GameWindow : public QWidget {
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr)
        : QWidget(parent), game_() {
        // Instantiate players and add to game
        players_.push_back(new coup::Governor(game_, "Moshe"));
        players_.push_back(new coup::Spy(game_, "Yossi"));
        players_.push_back(new coup::Baron(game_, "Meirav"));
        players_.push_back(new coup::General(game_, "Reut"));
        players_.push_back(new coup::Judge(game_, "Gilad"));
        players_.push_back(new coup::Merchant(game_, "Noa"));
        for (auto *p : players_) game_.addPlayer(p);

        // UI setup
        auto *mainLayout = new QVBoxLayout(this);
        currentLabel = new QLabel(this);
        coinLabel = new QLabel(this);
        mainLayout->addWidget(currentLabel);
        mainLayout->addWidget(coinLabel);

        targetCombo = new QComboBox(this);
        mainLayout->addWidget(targetCombo);

        auto *buttonLayout = new QHBoxLayout();
        incomeBtn = new QPushButton("Income", this);
        foreignAidBtn = new QPushButton("Foreign Aid", this);
        coupBtn = new QPushButton("Coup", this);
        specialBtn = new QPushButton(this);
        buttonLayout->addWidget(incomeBtn);
        buttonLayout->addWidget(foreignAidBtn);
        buttonLayout->addWidget(coupBtn);
        buttonLayout->addWidget(specialBtn);
        mainLayout->addLayout(buttonLayout);

        connect(incomeBtn, &QPushButton::clicked, this, &GameWindow::onIncome);
        connect(foreignAidBtn, &QPushButton::clicked, this, &GameWindow::onForeignAid);
        connect(coupBtn, &QPushButton::clicked, this, &GameWindow::onCoup);
        connect(specialBtn, &QPushButton::clicked, this, &GameWindow::onSpecial);

        updateUI();
    }

private slots:
    void onIncome() {
        auto *curr = game_.currentPlayer();
        try {
            curr->gather();
        } catch (const std::exception &e) {
            QMessageBox::warning(this, "Error", e.what());
        }
        updateUI();
    }
    void onForeignAid() {
        auto *curr = game_.currentPlayer();
        try {
            curr->tax();
        } catch (const std::exception &e) {
            QMessageBox::warning(this, "Error", e.what());
        }
        updateUI();
    }
    void onCoup() {
        auto *curr = game_.currentPlayer();
        QString name = targetCombo->currentText();
        auto *target = findPlayerByName(name.toStdString());
        try {
            curr->coup(*target);
        } catch (const std::exception &e) {
            QMessageBox::warning(this, "Error", e.what());
        }
        updateUI();
    }
    void onSpecial() {
        auto *curr = game_.currentPlayer();
        switch (specialAction) {
            case ActionType::Tax: {
                try { static_cast<coup::Governor*>(curr)->tax(); }
                catch (const std::exception &e) { QMessageBox::warning(this, "Error", e.what()); }
                break;
            }
            case ActionType::Spy: {
                QString name = targetCombo->currentText();
                auto *t = findPlayerByName(name.toStdString());
                try { static_cast<coup::Spy*>(curr)->Spy(); }
                catch (const std::exception &e) { QMessageBox::warning(this, "Error", e.what()); }
                break;
            }
            case ActionType::Invest: {
                try { static_cast<coup::Baron*>(curr)->invest(); }
                catch (const std::exception &e) { QMessageBox::warning(this, "Error", e.what()); }
                break;
            }
            case ActionType::Protect: {
                try { static_cast<coup::General*>(curr)->isCoupUndo(); }
                catch (const std::exception &e) { QMessageBox::warning(this, "Error", e.what()); }
                break;
            }
            case ActionType::Bribe: {
                QString name = targetCombo->currentText();
                auto *j = dynamic_cast<coup::Judge*>(findPlayerByName(name.toStdString()));
                try { curr->bribe(); }
                catch (const std::exception &e) { QMessageBox::warning(this, "Error", e.what()); }
                break;
            }
            default: break;
        }
        updateUI();
    }

private:
    coup::Game game_;
    std::vector<coup::Player*> players_;
    QLabel *currentLabel;
    QLabel *coinLabel;
    QComboBox *targetCombo;
    QPushButton *incomeBtn;
    QPushButton *foreignAidBtn;
    QPushButton *coupBtn;
    QPushButton *specialBtn;
    ActionType specialAction = ActionType::None;

    void updateUI() {
        auto *curr = game_.currentPlayer();
        currentLabel->setText("Turn: " + QString::fromStdString(curr->getName()));
        coinLabel->setText("Coins: " + QString::number(curr->getCoins()));

        targetCombo->clear();
        auto names = game_.players();
        for (const auto &nm : names) {
            if (nm != curr->getName())
                targetCombo->addItem(QString::fromStdString(nm));
        }

        // Determine special action
        incomeBtn->setEnabled(true);
        foreignAidBtn->setEnabled(true);
        coupBtn->setEnabled(curr->getCoins() >= 7);
        specialBtn->setEnabled(true);

        if (dynamic_cast<coup::Governor*>(curr)) {
            specialBtn->setText("Tax"); specialAction = ActionType::Tax;
        } else if (dynamic_cast<coup::Spy*>(curr)) {
            specialBtn->setText("Spy"); specialAction = ActionType::Spy;
        } else if (dynamic_cast<coup::Baron*>(curr)) {
            specialBtn->setText("Invest"); specialAction = ActionType::Invest;
        } else if (dynamic_cast<coup::General*>(curr)) {
            specialBtn->setText("Protect"); specialAction = ActionType::Protect;
        } else if (dynamic_cast<coup::Judge*>(curr)) {
            specialBtn->setText("Bribe"); specialAction = ActionType::Bribe;
        } else {
            specialBtn->setText(""); specialBtn->setEnabled(false);
            specialAction = ActionType::None;
        }
    }

    coup::Player* findPlayerByName(const std::string &name) {
        for (auto *p : players_) {
            if (p->getName() == name) return p;
        }
        return nullptr;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GameWindow w;
    w.show();
    return app.exec();
}

#include "main_gui.moc"
