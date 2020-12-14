#include "ui.hpp"

 Win::Win(QWidget* parent) :QWidget(parent) {
    //Menu
	setWindowTitle("Plot builder");
	label = new QLabel("Choose a photo with digits or press the exit button", this);
	exitButton = new QPushButton("Exit", this);
	chooseButton = new QPushButton("Choose file", this);
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(label);
	layout->addWidget(chooseButton);
	layout->addWidget(exitButton);
	connect(exitButton, SIGNAL(clicked(bool)),
		this, SLOT(close()));
	connect(chooseButton, SIGNAL(clicked(bool)),
		this, SLOT(clicked_choose()));
 }

void Win::clicked_choose() {
	QString path_ = QFileDialog::getOpenFileName(this, QObject::tr("Choose file"), QDir::homePath(),
		QObject::tr("Photo (*.png);;All files (*.*)"));
	this->set_path(path_);
    if (!(path_.isEmpty())) {
        this->photo_processing();
        if (!(this->is_error())) {
            //Вызов выбора типа графика
            AnotherWin AnWin;
            AnWin.set_data(get_data());
            AnWin.show();
            AnWin.exec();
        }
    }
    else {
        QMessageBox::information(this, tr("Error"),
            tr("Path is not selected. Try again."));
    }
}

void Win::error_occured() {
    error = true;
}

bool Win::is_error() {
    return error;
}

void Win::set_path(const QString& path_) {
	path = path_;
}

QString Win::get_path() {
    return path;
}

std::pair<std::vector<double>, std::vector<double>> Win::get_data() {
    return data;
}

void Win::photo_processing() {
    std::string path_to_photo = get_path().toUtf8().constData();
    std::string outText;
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    if (api->Init("..\\..\\..\\files\\tessdata\\", "eng")) {
        this->error_occured();
        QMessageBox::information(this, tr("Error"),
            tr("Could not initialize tesseract."));
        return;
    }
    Pix* image = pixRead(path_to_photo.c_str());
    api->SetImage(image);
    outText = api->GetUTF8Text();
    api->End();
    pixDestroy(&image);
    //Проверка считывания
    for (int i = 0; i < outText.size(); i++) {  
       if ((outText[i] > '9') || (outText[i] < '0')) {
           if ((outText[i] != '-') && (outText[i] != ' ') && (outText[i] != '\n') && (outText[i] != '.')) {
               this->error_occured();
               QMessageBox::information(this, tr("Error"),
                   tr("Input is not a number or Tesseract interpretted it wrong. Try again. Input is:\n") + QString::fromStdString(outText));
               return;
           }
       }
    }
    //QMessageBox::information(this, tr("Input"),
       // tr("Input is: \n") + QString::fromStdString(outText));

    std::string x, y, tmp;
    std::vector<double> x_vec, y_vec;
    x = outText.substr(0, outText.find('\n'));
    y = outText.substr(x.length() + 1, outText.find('\n', x.length() + 1) - 1);

    //Извлечь x
    for (int i = 0; i < x.size(); i++) {
        if (std::isdigit(x[i]) || x[i] == '-' || x[i] == '.') {
            tmp.push_back(x[i]);
            if (x[i + 1] == ' ' || i + 1 >= x.size()) {
                x_vec.push_back(std::stod(tmp));
                tmp = "";
            }
        }
    }
    //Извлечь y
    for (int i = 0; i < y.size(); i++) {
        if (std::isdigit(y[i]) || y[i] == '-' || y[i] == '.') {
            tmp.push_back(y[i]);
            if (y[i + 1] == ' ' || i + 1 >= y.size() || y[i + 1] == '\n') {
                y_vec.push_back(std::stod(tmp));
                tmp = "";
            }
        }
    }

    //Проверка равенства количества координат
    if (x_vec.size() != y_vec.size()) {
        std::cout << "That is x " << x << std::endl;
        std::cout << "That is y " << y << std::endl;
        this->error_occured();
        QMessageBox::information(this, tr("Error"),
             tr("X vector size is no equal to Y vector size. Try again.\n") + 
            "That is x: " + QString::fromStdString(x) + "\n" +
            "That is y " + QString::fromStdString(y));
        return;
    }
    QMessageBox::information(this, tr("X and Y"),
        tr("That is x: ") + QString::fromStdString(x) + "\n" +
        "That is y: " + QString::fromStdString(y));
    data = std::make_pair(x_vec, y_vec);
}

AnotherWin::AnotherWin(QWidget* parent) {
    //Выбор типа графа
    setWindowTitle("Graph type");
    label1 = new QLabel("Choose a type of graph to be build", this);
    linearButton = new QPushButton("Linear graph", this);
    logButton = new QPushButton("Logarithmic graph", this);
    QHBoxLayout* layout1 = new QHBoxLayout(this);
    layout1->addWidget(label1);
    layout1->addWidget(linearButton);
    layout1->addWidget(logButton);
    connect(linearButton, SIGNAL(clicked(bool)),
        this, SLOT(clicked_linear()));
    connect(logButton, SIGNAL(clicked(bool)),
        this, SLOT(clicked_log()));
}

void AnotherWin::clicked_linear() {
    drawer object;
    object.set_linear();
    object.cicle(data_.first, data_.second);
}

void AnotherWin::clicked_log() {
    for (int i = 0; i < data_.first.size(); i++) {
        if (data_.first[i] <= 0 || data_.second[i] <= 0) {
            QMessageBox::information(this, tr("Error"),
                tr("Logarithmic scale grapth can`t be built using negative numbers"));
            return;
        }
    }
    drawer object;
    object.set_log();
    object.cicle(data_.first, data_.second);
}

void AnotherWin::set_data(const std::pair<std::vector<double>, std::vector<double>>& data1) {
    data_ = data1;
}

#include "moc_ui.cpp"
