#include "mainwindow.h"
#include "./ui_mainwindow.h"

void MainWindow::createBlackButtonMatrix() {
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 10; ++col) {
            QPushButton* button = new QPushButton("Yours" + QString::number(row) + QString::number(col), ui->page_2);
            button->setGeometry(50 * row + 50, 50 * col + 50, 50, 50);

            Player::getPublicMatrix()[row][col] = { button, TileStatus::HIDDEN };
        }
    }

    // 1280 / 2 = 740 + 50 = 790
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 10; ++col) {
            QPushButton* button = new QPushButton("Enemy" + QString::number(row) + QString::number(col), ui->page_2);
            button->setGeometry(740 + 50 * row, 50 * col + 50, 50, 50);

            connect(button, &QPushButton::clicked, this, &MainWindow::handleEnemyMatrixButtonClick);
            Enemy::getPublicMatrix()[row][col] = { button, TileStatus::HIDDEN };
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->framePort->hide();
    ui->readyLabel->hide();
    createBlackButtonMatrix();

    ShipWidget* shipsObj = new ShipWidget(this);
    shipsObj->fillUpShips();
    shipsObj->drawShips();
    ui->page_2->installEventFilter(this);

    MouseReleaseFilter *mouseReleaseFilter = new MouseReleaseFilter;
    this->installEventFilter(mouseReleaseFilter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleEnemyMatrixButtonClick(){
    if (!Conf::ready) {
        std::cout  << "Press that u are ready" << std::endl;
        return;
    }

    if (ConfS::getPlayerStep())
    {
        QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
        if (clickedButton) {
            qDebug() << "Button clicked: " << clickedButton->text();
            int x = clickedButton->text()[clickedButton->text().size() - 2].digitValue();
            int y = clickedButton->text()[clickedButton->text().size() - 1].digitValue();

            std::cout << "SHOT WAS MADEN AT x: " << x << "y: " << y << std::endl;
            if (!Player::makeShot(x, y)){
                ConfS::setPlayerStep(false);
                ConfS::setPauseThread(false);
            }
        }
    } else {
        std::cout << "That not ours step" << std::endl;
    }
}

void MainWindow::on_continueBotButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    Conf::gameMode = 'b';
    Bot::generateShipsOnMatrix();

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << (int) Bot::getPrivateMatrix()[i][j] << ' ';
        }
        std::cout << std::endl; // Start a new line for the next row
    }
}

void MainWindow::on_continueNetButton_clicked()
{
    ui->framePort->show();
}

void MainWindow::on_submitNetButton_clicked()
{
    int pos = 0;
    QIntValidator v(1024, 65534, this);

    QString userInput = ui->portInput->toPlainText();
    if (v.validate(userInput, pos) == QValidator::Invalid) {
        std::cout << "Enter value userInput" << std::endl;
        QMessageBox::question(this, "Error", "Enter valid port", QMessageBox::Ok);

        Conf::port = userInput.toInt();
        Conf::host = ui->hostCheckBox->checkState() == 2 ? true : false;
        Conf::gameMode = 'n';
    } else {
        ui->stackedWidget->setCurrentIndex(1);
        this->createBlackButtonMatrix();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    ShipStruct* ship = ShipWidget::findShipByMouse(event->pos().x(), event->pos().y());

    if (ship == nullptr) {
        return;
    }

    int counter = 0;
    if (ship->relative_position == Positioning::HORIZONTAL){
        for (auto& button : ship->body)
        {
            button->setGeometry(event->pos().x() - 25 + counter * 50, event->pos().y() - 25, 50 , 50);
            counter++;
        }
    } else {
        for (auto& button : ship->body) {
            button->setGeometry(event->pos().x() - 25, event->pos().y() - 25 + counter * 50, 50 , 50);
            counter++;
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (Conf::gameStarted) {
        return;
    }
//    if (Player::isShipPlacementFinished())
//    {
        if (!Conf::ready) {
            ui->NotReadyLabel->hide();
            ui->readyLabel->show();
            Conf::ready = true;
        } else {
            ui->NotReadyLabel->show();
            ui->readyLabel->hide();
            Conf::ready = false;
        }
//    } else {
//        QMessageBox::question(this, "Error", "Pls fill up ships firstly", QMessageBox::Ok);
//    }
}
