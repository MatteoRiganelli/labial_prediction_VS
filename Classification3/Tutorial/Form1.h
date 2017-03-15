#pragma once


#include "stdafx.h"
#include "ImageProcess.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include "find_word.hpp"
//#include "eye_detect.hpp"
#include <stdio.h> 
#include <stdlib.h>
#include <string>
#include <direct.h>
#include "Form_About.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>


 
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
//using namespace cv;
using namespace std;

//funzioni 
//converte int in string
string inttostr(int input);
//restituisce striga di comando eseguito da terminale
string GetStdoutFromCommand(string cmd);
//rimuovere specifico carattere 
string RemoveChar(string str, char c);
//crea file SysnetWord per rete Caffe
void createSynsetWord();

//initialize component here to get access public class
CvCapture* capture;

//per salvataggio video
VideoCapture vid("out.avi"); 
Mat frame1; 
VideoWriter video("out.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, cv::Size(640, 480), true);
int counter = 0;
//---------------------
//frame acquisito
IplImage* frame;
//regione bocca 
IplImage *mouthRegion;
//per rilevamento volto
ObjectDetector* faceDetector = new HaarCascadeObjectDetector("haarcascade_frontalface_alt.xml");

//IplImage* result; (non utilizzata)

//rettangolo per ritaglio
Rect croppedRectangle;

//per inserimento carattere da tastiera (non utilizzata)
//int key; 

//numero frame acquisiti
long int framenumber = 0;

bool mouthFound = false;
Mat myMat;
Mat croppedImage;

//inizia a salvare immagini
bool inizia = false;

//camera accesa
bool camera_on = false;

//contatore per salvataggio immagini
int photocount = 1; //initialize image counter

int N_MIN = 0; //prima classe
int regola_index = 0; // per stabilire tramite pulsanti quale classe classificare
int NUM_CLASSI = 9; //ultima classe

__int32 num_item_per_class; //numero istanze per classe

int fino_a = 0; //aiuta il programma a salvare le immagini appunto fino_a num_iter per class (non utilizzata qua)

vector<int> classified_visemes; //visemi classificati
vector<string> immagini; //immagini da classificare


namespace Tutorial {
	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			//cambio directory principlae per poter effettuare più facilmente la classificazione dei visemi
			//che vengono salvati sempre nella cartella principale di caffe in caffe/images
			chdir("/Projects/prova/caffe");
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected: 
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	public: System::Windows::Forms::TextBox^  textBox1;
	public: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBoxViseme;
	private: System::Windows::Forms::Button^  buttonElabora;
	private: System::Windows::Forms::TextBox^  textBoxFrase;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBoxViseme = (gcnew System::Windows::Forms::TextBox());
			this->buttonElabora = (gcnew System::Windows::Forms::Button());
			this->textBoxFrase = (gcnew System::Windows::Forms::TextBox());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Black;
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pictureBox1->Location = System::Drawing::Point(12, 70);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(320, 240);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.BackgroundImage")));
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->button1->Location = System::Drawing::Point(354, 80);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(86, 85);
			this->button1->TabIndex = 1;
			this->button1->Text = L"ON";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// timer1
			// 
			this->timer1->Interval = 30;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(703, 24);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->aboutToolStripMenuItem,
					this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitToolStripMenuItem_Click);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(12, 316);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(386, 184);
			this->textBox1->TabIndex = 4;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Black;
			this->pictureBox2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pictureBox2->Location = System::Drawing::Point(465, 92);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(200, 200);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 5;
			this->pictureBox2->TabStop = false;
			// 
			// button2
			// 
			this->button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.BackgroundImage")));
			this->button2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(354, 192);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(86, 78);
			this->button2->TabIndex = 6;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(25, 44);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(184, 20);
			this->label1->TabIndex = 9;
			this->label1->Text = L"-CAMERA CAPTURE-";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(461, 44);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(212, 20);
			this->label2->TabIndex = 10;
			this->label2->Text = L"-MOUTH RECOGNITION-";
			// 
			// textBoxViseme
			// 
			this->textBoxViseme->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBoxViseme->Location = System::Drawing::Point(404, 316);
			this->textBoxViseme->Name = L"textBoxViseme";
			this->textBoxViseme->Size = System::Drawing::Size(287, 29);
			this->textBoxViseme->TabIndex = 11;
			// 
			// buttonElabora
			// 
			this->buttonElabora->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonElabora->Location = System::Drawing::Point(465, 397);
			this->buttonElabora->Name = L"buttonElabora";
			this->buttonElabora->Size = System::Drawing::Size(174, 59);
			this->buttonElabora->TabIndex = 12;
			this->buttonElabora->Text = L"Elabora";
			this->buttonElabora->UseVisualStyleBackColor = true;
			this->buttonElabora->Click += gcnew System::EventHandler(this, &Form1::buttonElabora_Click);
			// 
			// textBoxFrase
			// 
			this->textBoxFrase->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBoxFrase->Location = System::Drawing::Point(86, 506);
			this->textBoxFrase->Name = L"textBoxFrase";
			this->textBoxFrase->Size = System::Drawing::Size(535, 29);
			this->textBoxFrase->TabIndex = 13;
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::aboutToolStripMenuItem_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Gainsboro;
			this->ClientSize = System::Drawing::Size(703, 547);
			this->Controls->Add(this->textBoxFrase);
			this->Controls->Add(this->buttonElabora);
			this->Controls->Add(this->textBoxViseme);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Form1::Form1_FormClosed);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	System::String^ button_red = "C:/Users/Matteo/Documents/Visual Studio 2013/Projects/Classification3/Tutorial/button_red.png";
	System::String^ button_green = "C:/Users/Matteo/Documents/Visual Studio 2013/Projects/Classification3/Tutorial/button_green.png";
	System::String^ button2_red = "C:/Users/Matteo/Documents/Visual Studio 2013/Projects/Classification3/Tutorial/button2_red.png";
	System::String^ button2_green = "C:/Users/Matteo/Documents/Visual Studio 2013/Projects/Classification3/Tutorial/button2_green.png";

	//---------------------------------------------------------------------------------
	//---Buttone attiva-disattiva camera-----------------------------------------------
	//---------------------------------------------------------------------------------
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		
		//se camera è spenta, la accendo
		if (camera_on == false){
			camera_on = true;
			button1->BackgroundImage = System::Drawing::Image::FromFile(button_red);
			button1->Text = L"OFF";
		    capture = cvCreateCameraCapture(CV_CAP_ANY);
			
		    if (capture) {
				timer1->Start();
			}		 
		}
		//se camera è accesa la spengo
		else{
			//spengo pictureBox
			camera_on = false;
			button1->Text = L"ON";
			button1->BackgroundImage = System::Drawing::Image::FromFile(button_green);
			//immagine nera in picture box1
			pictureBox1->Image = gcnew    //replacement of cvShowImage
				System::Drawing::Bitmap(frame->width, frame->height, frame->widthStep,
				System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr) NULL);
			pictureBox1->Refresh();
			//riabilito textBox2
			//textBox2->Enabled = true; 
			cvReleaseCapture(&capture);

		}
		//num_visemi da salvare per ogni classe
		//System::String^ string_text_box2 = textBox2->Text;
		//num_item_per_class = System::Int32::Parse(string_text_box2);
		
	}

	//---------------------------------------------------------------------------------
	//---Buttone attiva-disattiva acquisizione bocca-----------------------------------------------
	//---------------------------------------------------------------------------------
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		if (camera_on == true){
			if (inizia == false) {
				button2->BackgroundImage = System::Drawing::Image::FromFile(button2_red);
				inizia = true;
				//sndPlaySound("beep_yes", SND_ASYNC);
			}
			else {
				inizia = false;
				button2->BackgroundImage = System::Drawing::Image::FromFile(button2_green);
				//immagine nera in picture box1
				pictureBox2->Image = gcnew    //replacement of cvShowImage
					System::Drawing::Bitmap(frame->width, frame->height, frame->widthStep,
					System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr) NULL);
				pictureBox2->Refresh();
			}
			/*
			textBox1->Text = textBox1->Text + "\r\n" + inizia;
			textBox1->SelectionStart = textBox1->Text->Length;
			textBox1->ScrollToCaret();
			*/
		}
		
	}

	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		//stringa per salvataggio immagine
		string imagename;

		//numero frame acquisiti
		framenumber += 1;

		//textBoxViseme->Text =  "\n" + framenumber;

		//acquisizione frame
		frame = cvQueryFrame(capture);
		//ruoto di 180 l'immagine sul suo asse verticale
		cvFlip(frame, frame, 180);

		if (frame != NULL){
			video.write(frame); //scrive su out.avi
			//if (conta < fino_a)
			//{
			CvSize s = cvGetSize(frame);
			int d = frame->depth;
			int c = frame->nChannels;
			mouthRegion = cvCreateImage(s, d, c); // (s, 8, 3)
			//croppedRectangle = Rect(300, 300, 100, 100); //coordinate crop + width,height crop 
			//result = cvCreateImage(s, d, c); // (s, 8, 3) 
			cvCopy(frame, frame); //it's important if u make the image in 3 channel or filtering
			Mat eccolo;
			try{
				eccolo = findLip(frame, faceDetector, mouthRegion, mouthFound);
			}
			catch (cv::Exception &e){ cout << e.what() << endl; }
			if (!eccolo.empty())
			{

				myMat = mouthRegion;
				croppedRectangle = Rect(300, 300, 100, 100); //coordinate crop + width,height crop 
				croppedImage = myMat(croppedRectangle);

				IplImage prova = croppedImage; //provare o con 'eccolo' o con 'croppedImage' con 'eccolo' rimane fissa 
				IplImage* somePointer = &prova;

				//la mostro nella pictureBox2
				pictureBox2->Image = gcnew    //replacement of cvShowImage
					System::Drawing::Bitmap(somePointer->width, somePointer->height, somePointer->widthStep,
					System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr) somePointer->imageData);
				pictureBox2->Refresh();

			}
			else
			{

				inizia = false;
				button2->BackgroundImage = System::Drawing::Image::FromFile(button2_green);
				//immagine nera in picture box1
				pictureBox2->Image = gcnew    //replacement of cvShowImage
					System::Drawing::Bitmap(frame->width, frame->height, frame->widthStep,
					System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr) NULL);
				pictureBox2->Refresh();

				/*
				//SALVO IMMAIGNI DA FRAME VIDEO
				if (!vid.isOpened()) //vid è sempre out.avi, quindi se cè qualcosa OK!
				textBoxViseme->Text = "ERROR";
				stringstream file;
				vid.read(frame1);

				if (frame1.empty()) textBoxViseme->Text = "ERROR";

				file << "C:/Users/Matteo/Documents/Visual Studio 2013/Projects/Classification3/Tutorial/videoImage/image" << counter << ".jpg";
				counter++;
				imwrite(file.str(), frame1);
				*/
			}
			if (inizia == true && framenumber %5 == 0)
			{
				imagename = "";

				//scrivo stringa per immagine
				imagename = "images/image" + inttostr(photocount) + ".JPEG";
				immagini.push_back("images\\image" + inttostr(photocount) + ".JPEG");

				//converto string in System::String per poterlo stampare su TextBox
				//System::String^ string = gcnew System::String(imagename.c_str());
				// e la stampo su textBox
				//textBox1->Text = textBox1->Text + "\r\n" + string;
				//textBox1->SelectionStart = textBox1->Text->Length;
				//textBox1->ScrollToCaret();

				//questo serve per poter salvare l'immagine 
				vector<int> compression_params;
				//vector that stores the compression parameters of the image
				compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
				//specify the compression technique
				compression_params.push_back(100); //specify the compression quality

				//incremento photocount per contarore immagini salvate
				photocount++;

				//salvo l'immagine
				imwrite(imagename, croppedImage, compression_params); //provare o con 'eccolo' o con 'croppedImage'
					
				
			}
			pictureBox1->Image = gcnew    //replacement of cvShowImage
				System::Drawing::Bitmap(frame->width, frame->height, frame->widthStep,
				System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr) frame->imageData);
			pictureBox1->Refresh();
		}

	}
	

	private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 cvReleaseCapture(&capture);
				 createSynsetWord();
				 Application::Exit();
			 }

	private: System::Void Form1_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				cvReleaseCapture(&capture);
				createSynsetWord();
				Application::Exit();
	}


//premendolo elabora dati ottenuti e alla fine ripristina impostazioni default per nuova elaborazione
private: System::Void buttonElabora_Click(System::Object^  sender, System::EventArgs^  e) {
	//per predizione parola
	Find_Word FW = Find_Word();
	//EyeDetector ED = EyeDetector();
	//VISEME 5
	//string proto_path = "examples\\viseme5\\lenet.prototxt";
	//string model_path = "examples\\viseme5\\viseme_snap_iter_150.caffemodel";
	//string binaryproto_path = "data\\viseme3\\imagenet_mean.binaryproto";
	//string synsetwords_path = "data\\viseme3\\synset_words.txt";

	//VISEME 7
	string proto_path = "examples\\viseme7\\lenet.prototxt";
	string model_path = "examples\\viseme7\\viseme_snap_iter_150.caffemodel";
	string binaryproto_path = "data\\viseme5\\imagenet_mean.binaryproto";
    string synsetwords_path = "data\\viseme5\\synset_words.txt";

	int visemeCode;
	bool completeWord = false;
	unsigned int parola = 0;
	vector<string> wordsFound;
	//mi sposto sulla directory to 'caffe' per eseguire i comandi

	//textBox1->Text = textBox1->Text + "CIAO SONO MATTEO" + "\r\n";
		//textBox1->SelectionStart = textBox1->Text->Length;
		//textBox1->ScrollToCaret();

	textBox1->Text = textBox1->Text + "immagini size= " +immagini.size() + "\n";

	for (int t = 0; t<immagini.size(); ++t){
		System::String^ string = gcnew System::String(immagini.at(t).c_str());
		textBox1->Text = textBox1->Text + string + "\r\n";
		textBox1->SelectionStart = textBox1->Text->Length;
		textBox1->ScrollToCaret();
		//cout << "Eccolo->" << immagini.at(t) << endl;
	}

	//per ogni immagine dal classificare
	for (int t = 0; t<immagini.size(); ++t){
		fstream file("result.txt", ios::out); //apre il file in scrittura (cancellando quello che già c'era)
		if (!file) {
			textBox1->Text = textBox1->Text + "Impossibile aprire file di output!";
		}
		string image_path = immagini.at(t);
		//cout << "IMAGE_PATH= "<<image_path << endl;
		//comando da eseguire
		string result = GetStdoutFromCommand("build\\examples\\cpp_classification\\Release\\classification.exe " + proto_path + " " + model_path + " " + binaryproto_path + " " + synsetwords_path + " " + image_path);
		//cout << "RESULT" << endl;
		//cout << result << endl;
		//cout << "---" << endl;

		//scrivo rsultato su file .txt
		
		file << result << endl;

		vector<string> righe;
		righe.clear();
		fstream in("result.txt", ios::in);
		string s = "";
		string value;
		while (getline(in, s))
		{
			istringstream iss(s);
			while (iss >> value) {
				righe.push_back(value);
			}
		}
		//cout << endl;
		for (int i = 0; i< righe.capacity(); i++){
			if (i == 7){ //se sono al elemento 7, quindi la l'elemento dove c'è il risultato
				//cout << i << " - " << righe[i] << endl;
				//textBox1->Text = textBox1->Text + i + " - ";
				//textBox1->SelectionStart = textBox1->Text->Length;
				//textBox1->ScrollToCaret();
				//cout << righe[i] << endl;
				string s = righe[i];
				//cout << s << endl;
				s = RemoveChar(s, '"'); //rimuovo carattetere ' " '
				//cout << "s=" << s << endl;
				int n = atoi(s.c_str());
				//printf("NUMBER=%d\n", n);
				textBox1->Text = textBox1->Text + "NUMBER= " + n + "\r\n";
				textBox1->SelectionStart = textBox1->Text->Length;
				textBox1->ScrollToCaret();
				//classified_visemes.push_back(n);
				FW.add_classified_visemes(n);
			}
		}
		in.close();
		file.close();
		for (int t = 0; t<FW.size_classified_visemes(); ++t){
			textBox1->Text = textBox1->Text + "CLASSIFIED_VISEME -> " + FW.x_element_classified_visemes(t) + "\r\n";
			textBox1->SelectionStart = textBox1->Text->Length;
			textBox1->ScrollToCaret();
			//cout << "CLASSIFIED_VISEME->" << t << " -> " << FW.x_element_classified_visemes(t) << endl;
		}
		//VISEMA CLASSIFICATO
		visemeCode = FW.last_classified_visemes();
		//visemeCode = classified_visemes.back(); // passo sempre l'ultimo visema classificato
		/*
		if((visemeCode==7 || visemeCode==5 || visemeCode==6) && FW.sizeVisemeList() >=5){ // er aggiustare il 7 finale, provare
		visemeCode = 9;
		}
		*/
		completeWord = FW.addViseme(visemeCode);
		cout << "COMPLETE_WORD= " << completeWord << endl;
		textBox1->Text = textBox1->Text + "COMPLETE_WORD= " + completeWord + "\r\n";
		textBox1->SelectionStart = textBox1->Text->Length;
		textBox1->ScrollToCaret();
		
		if (completeWord)
		{
			//int fontFace = CV_FONT_HERSHEY_DUPLEX;
			int fontFace = CV_FONT_ITALIC;
			double fontScale = 1.5;
			int thickness = 3;
			//cvPutText(result, "Attendere, ricerca parola in corso...", Point(20, 100), &font1, cvScalar(255, 0, 0, 0));
			textBox1->Text = textBox1->Text + "Attendere, ricerca parola in corso...\r\n";
			textBox1->SelectionStart = textBox1->Text->Length;
			textBox1->ScrollToCaret();
			wordsFound.clear();
			wordsFound = FW.searchWord();
			if (wordsFound.size() == 0)
			{
				//putText(word, ":( - Nessuna parola trovata,", Point(20, 50), fontFace, 1, cvScalar(0, 0, 255, 0), 2, 8);
				//putText(word, "chiudere gli occhi per continuare", Point(20, 100), fontFace, 1, cvScalar(255, 0, 0, 0), 2, 8);
				textBox1->Text = textBox1->Text + "Nessuna parola trovata...\r\n";
				textBox1->Text = textBox1->Text + "Chiudere gli occhi per continuare...\r\n";
				textBox1->SelectionStart = textBox1->Text->Length;
				textBox1->ScrollToCaret();
				//while ((key = waitKey(30)) != 'd'); //mettere anche  || ((key = waitKey(30)) != 'd')     ((ED.detect() == 0))
				//sndPlaySound("C://Users//Matteo//Documents//NetBeansProjects//Classification2//beep_yes", SND_ASYNC);
			}
			else
			{
				Mat dst;
				System::String^ words_found_zero = gcnew System::String(wordsFound[0].c_str());
				textBoxFrase->Text = textBoxFrase->Text + " " +words_found_zero;
				textBox1->Text = textBox1->Text + "--" + words_found_zero + "\r\n";
				textBox1->SelectionStart = textBox1->Text->Length;
				textBox1->ScrollToCaret();

				for (int w = 0; w<wordsFound.size(); w++)
				{
					
					System::String^ words_found_w = gcnew System::String(wordsFound[w].c_str());
					textBox1->Text = textBox1->Text + words_found_w + "\r\n";
					textBox1->SelectionStart = textBox1->Text->Length;
					textBox1->ScrollToCaret();

				}

				//while ((key = waitKey(30)) != 'd') //ED.detect() == 1*
					// se si chiudono gli occhi(ED.detect()==1) si cancella la prima parola e si prosegue con la selezione
					// se si rimane con gli occhi aperti (ED.detect()==0) si seleziona la parola
				{
					//sndPlaySound("C://Users//Matteo//Documents//NetBeansProjects//Classification2//beep_no", SND_ASYNC);
					wordsFound.erase(wordsFound.begin());
					if (wordsFound.size() == 0)
					{
						textBox1->Text = textBox1->Text + "Suggerimenti finiti" + "\r\n";
						textBox1->Text = textBox1->Text + "chiudere gli occhi per continuare" + "\r\n";
						textBox1->SelectionStart = textBox1->Text->Length;
						textBox1->ScrollToCaret();
						//while ((key = waitKey(30)) != 'd');     // attende che l'utente chiuda gli occhi (ED.detect()==1) per continuare
						//sndPlaySound("C://Users//Matteo//Documents//NetBeansProjects//Classification2//beep_yes", SND_ASYNC);
						break;
					}
					else
					{
						System::String^ words_found_zero = gcnew System::String(wordsFound[0].c_str());
						textBox1->Text = textBox1->Text + words_found_zero + "\r\n";
						textBox1->SelectionStart = textBox1->Text->Length;
						textBox1->ScrollToCaret();

						for (int w = 1; w<wordsFound.size(); w++)
						{
							
							System::String^ words_found_w = gcnew System::String(wordsFound[w].c_str());
							textBox1->Text = textBox1->Text + words_found_w + "\r\n";
							textBox1->SelectionStart = textBox1->Text->Length;
							textBox1->ScrollToCaret();
						}
					}
				}
				//sndPlaySound("C://Users//Matteo//Documents//NetBeansProjects//Classification2//beep_yes", SND_ASYNC);
				if (wordsFound.size() != 0){
					//putText(frase, wordsFound[0] + " ", Point(20 + 150 * parola, 50), fontFace, 1, Scalar::all(255), 2, 8);
					System::String^ words_found_zero = gcnew System::String(wordsFound[0].c_str());
					
					textBox1->Text = textBox1->Text + words_found_zero + "\r\n";
					textBox1->SelectionStart = textBox1->Text->Length;
					textBox1->ScrollToCaret();
				}
			}
			//photocount = 0;
			FW.clear_classified_visemes();
			completeWord = false;
		}
		

	}

	classified_visemes.clear();
	immagini.clear();
	
	//elimino tutte le immagini in images
	/*
	for (int i = 1; i < photocount; i++){
		string s = "images/image" + inttostr(i) + ".JPEG";
		const char* c = s.c_str();

		if (remove(c) != 0){
			textBox1->Text = textBox1->Text + "ERRORE ELIMINAZIONE" + "\r\n";
			textBox1->SelectionStart = textBox1->Text->Length;
			textBox1->ScrollToCaret();
		}
		else
		{
			textBox1->Text = textBox1->Text + "IMAGES VUOTA" + "\r\n";
			textBox1->SelectionStart = textBox1->Text->Length;
			textBox1->ScrollToCaret();
		}
	}
	*/
	//-------------------------------------
	/*
	textBox1->Text = textBox1->Text + "CLASSIFIED_VISEME -> " + 8 + "\r\n";
	textBox1->SelectionStart = textBox1->Text->Length;
	textBox1->ScrollToCaret();
	textBox1->Text = textBox1->Text + "CLASSIFIED_VISEME -> " + 8 + "\r\n";
	textBox1->SelectionStart = textBox1->Text->Length;
	textBox1->ScrollToCaret();
	textBox1->Text = textBox1->Text + "CLASSIFIED_VISEME -> " + 8 + "\r\n";
	textBox1->SelectionStart = textBox1->Text->Length;
	textBox1->ScrollToCaret();
	textBox1->Text = textBox1->Text + "CLASSIFIED_VISEME -> " + 0 + "\r\n";
	textBox1->SelectionStart = textBox1->Text->Length;
	textBox1->ScrollToCaret();
	textBox1->Text = textBox1->Text + "CLASSIFIED_VISEME -> " + 0 + "\r\n";
	textBox1->SelectionStart = textBox1->Text->Length;
	textBox1->ScrollToCaret();
	textBox1->Text = textBox1->Text + "CLASSIFIED_VISEME -> " + 0 + "\r\n";
	textBox1->SelectionStart = textBox1->Text->Length;
	textBox1->ScrollToCaret();
	textBox1->Text = textBox1->Text + "CLASSIFIED_VISEME -> " + 3 + "\r\n";
	textBox1->SelectionStart = textBox1->Text->Length;
	textBox1->ScrollToCaret();
	textBox1->Text = textBox1->Text + "CLASSIFIED_VISEME -> " + 3 + "\r\n";
	textBox1->SelectionStart = textBox1->Text->Length;
	textBox1->ScrollToCaret();
	textBox1->Text = textBox1->Text + "CLASSIFIED_VISEME -> " + 3 + "\r\n";
	textBox1->SelectionStart = textBox1->Text->Length;
	textBox1->ScrollToCaret();
	textBox1->Text = textBox1->Text + "CLASSIFIED_VISEME -> " + 9 + "\r\n";
	textBox1->SelectionStart = textBox1->Text->Length;
	textBox1->ScrollToCaret();
	textBox1->Text = textBox1->Text + "CLASSIFIED_VISEME -> " + 9 + "\r\n";
	textBox1->SelectionStart = textBox1->Text->Length;
	textBox1->ScrollToCaret();
	textBox1->Text = textBox1->Text + "CLASSIFIED_VISEME -> " + 9 + "\r\n";
	textBox1->SelectionStart = textBox1->Text->Length;
	textBox1->ScrollToCaret();
	textBoxFrase->Text = textBoxFrase->Text + "CIAO SONO MATTEO ";
	*/
	photocount = 1;
}

private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Form_About^ form_informazioni = gcnew Form_About();
	form_informazioni->ShowDialog();
}
};

}

string inttostr(int input)
{
	stringstream ss;
	ss << input;
	return ss.str();
}

//restituisce lo std output di un comando eseguito da terminale sottoforma di stringa
string GetStdoutFromCommand(string cmd) {
	string data;
	FILE * stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	cmd.append(" 2>&1");

	stream = _popen(cmd.c_str(), "r");
	if (stream) {
		while (!feof(stream))
			if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
		_pclose(stream);
	}
	return data;
}

//rimuove carattere x data una stringa y
string RemoveChar(string str, char c)
{
	string result;
	for (size_t i = 0; i < str.size(); i++)
	{
		char currentChar = str[i];
		if (currentChar != c)
			result += currentChar;
	}
	return result;
}

void createSynsetWord(){
	fstream f2("synset_word.txt", ios::out); //apre il file in scrittura (cancellando quello che già c'era
	for (int i = 0; i <= NUM_CLASSI; i++){
		cout << i << " " << "viseme" << i << endl;
		f2 << i << " " << "viseme" << i << endl;
	}

}



