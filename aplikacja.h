#pragma once
#include <string>
#include <iostream>
#include <msclr\marshal_cppstd.h>
#include "multifiltr.h"

namespace Multifiltr {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;

	/// <summary>
	/// Podsumowanie informacji o aplikacja
	/// </summary>
	public ref class aplikacja : public System::Windows::Forms::Form
	{
	public:
		aplikacja(void)
		{
			InitializeComponent();
			//
			//TODO: W tym miejscu dodaj kod konstruktora
			//
		}

	protected:
		/// <summary>
		/// Wyczyœæ wszystkie u¿ywane zasoby.
		/// </summary>
		~aplikacja()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::TextBox^ tSciezka;


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::RadioButton^ radioASM;
	private: System::Windows::Forms::RadioButton^ radioCPP;
	private: System::Windows::Forms::TrackBar^ trackBar;




	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ lWatki;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::PictureBox^ pictureBox4;
	private: System::Windows::Forms::PictureBox^ pictureBox5;
	private: System::Windows::Forms::PictureBox^ pictureBox6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ lCzas;

	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::TextBox^ tWywolania;

	private: System::Windows::Forms::Label^ lStan;


	protected:

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->tSciezka = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->radioASM = (gcnew System::Windows::Forms::RadioButton());
			this->radioCPP = (gcnew System::Windows::Forms::RadioButton());
			this->trackBar = (gcnew System::Windows::Forms::TrackBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->lWatki = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->lCzas = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->tWywolania = (gcnew System::Windows::Forms::TextBox());
			this->lStan = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(51, 415);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(124, 26);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Edytuj";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &aplikacja::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(240, 160);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// tSciezka
			// 
			this->tSciezka->Location = System::Drawing::Point(12, 196);
			this->tSciezka->Name = L"tSciezka";
			this->tSciezka->Size = System::Drawing::Size(231, 20);
			this->tSciezka->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 180);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(95, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Œcie¿ka do obrazu";
			// 
			// radioASM
			// 
			this->radioASM->AutoSize = true;
			this->radioASM->Checked = true;
			this->radioASM->Location = System::Drawing::Point(8, 20);
			this->radioASM->Name = L"radioASM";
			this->radioASM->Size = System::Drawing::Size(69, 17);
			this->radioASM->TabIndex = 4;
			this->radioASM->TabStop = true;
			this->radioASM->Text = L"kod ASM";
			this->radioASM->UseVisualStyleBackColor = true;
			// 
			// radioCPP
			// 
			this->radioCPP->AutoSize = true;
			this->radioCPP->Location = System::Drawing::Point(8, 43);
			this->radioCPP->Name = L"radioCPP";
			this->radioCPP->Size = System::Drawing::Size(77, 17);
			this->radioCPP->TabIndex = 5;
			this->radioCPP->TabStop = true;
			this->radioCPP->Text = L"kod C/C++";
			this->radioCPP->UseVisualStyleBackColor = true;
			// 
			// trackBar
			// 
			this->trackBar->Location = System::Drawing::Point(6, 371);
			this->trackBar->Maximum = 64;
			this->trackBar->Minimum = 1;
			this->trackBar->Name = L"trackBar";
			this->trackBar->Size = System::Drawing::Size(231, 45);
			this->trackBar->TabIndex = 6;
			this->trackBar->Value = 1;
			this->trackBar->Scroll += gcnew System::EventHandler(this, &aplikacja::trackBar1_Scroll);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 349);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(147, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Iloœæ uruchamianych w¹tków:";
			// 
			// lWatki
			// 
			this->lWatki->AutoSize = true;
			this->lWatki->Location = System::Drawing::Point(162, 349);
			this->lWatki->Name = L"lWatki";
			this->lWatki->Size = System::Drawing::Size(13, 13);
			this->lWatki->TabIndex = 9;
			this->lWatki->Text = L"1";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(9, 400);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(13, 13);
			this->label5->TabIndex = 10;
			this->label5->Text = L"1";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(221, 400);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(19, 13);
			this->label6->TabIndex = 11;
			this->label6->Text = L"64";
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->pictureBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox2->Location = System::Drawing::Point(292, 12);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(180, 120);
			this->pictureBox2->TabIndex = 12;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->pictureBox3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox3->Location = System::Drawing::Point(479, 12);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(180, 120);
			this->pictureBox3->TabIndex = 13;
			this->pictureBox3->TabStop = false;
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->pictureBox4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox4->Location = System::Drawing::Point(292, 159);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(180, 120);
			this->pictureBox4->TabIndex = 14;
			this->pictureBox4->TabStop = false;
			// 
			// pictureBox5
			// 
			this->pictureBox5->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->pictureBox5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox5->Location = System::Drawing::Point(479, 159);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(180, 120);
			this->pictureBox5->TabIndex = 15;
			this->pictureBox5->TabStop = false;
			// 
			// pictureBox6
			// 
			this->pictureBox6->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->pictureBox6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox6->Location = System::Drawing::Point(479, 305);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(180, 120);
			this->pictureBox6->TabIndex = 16;
			this->pictureBox6->TabStop = false;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(289, 135);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(112, 13);
			this->label7->TabIndex = 17;
			this->label7->Text = L"Skala odcieni szaroœci";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(289, 282);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(91, 13);
			this->label8->TabIndex = 18;
			this->label8->Text = L"Korekta kontrastu";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(476, 135);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(34, 13);
			this->label9->TabIndex = 19;
			this->label9->Text = L"Sepia";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(476, 282);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(61, 13);
			this->label10->TabIndex = 20;
			this->label10->Text = L"Solaryzacja";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(310, 371);
			this->label11->MinimumSize = System::Drawing::Size(120, 0);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(120, 13);
			this->label11->TabIndex = 21;
			this->label11->Text = L"Czas przetwarzania (s):";
			this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lCzas
			// 
			this->lCzas->AutoSize = true;
			this->lCzas->Location = System::Drawing::Point(310, 400);
			this->lCzas->MinimumSize = System::Drawing::Size(120, 0);
			this->lCzas->Name = L"lCzas";
			this->lCzas->Size = System::Drawing::Size(120, 13);
			this->lCzas->TabIndex = 22;
			this->lCzas->Text = L"0";
			this->lCzas->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->radioCPP);
			this->groupBox1->Controls->Add(this->radioASM);
			this->groupBox1->Location = System::Drawing::Point(12, 224);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(163, 71);
			this->groupBox1->TabIndex = 23;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Wykorzystywane biblioteki";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(476, 428);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(62, 13);
			this->label2->TabIndex = 24;
			this->label2->Text = L"Filtr Gaussa";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(13, 304);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(75, 13);
			this->label13->TabIndex = 25;
			this->label13->Text = L"Iloœæ wywo³añ";
			// 
			// tWywolania
			// 
			this->tWywolania->Location = System::Drawing::Point(12, 320);
			this->tWywolania->Name = L"tWywolania";
			this->tWywolania->Size = System::Drawing::Size(231, 20);
			this->tWywolania->TabIndex = 26;
			this->tWywolania->Text = L"1";
			// 
			// lStan
			// 
			this->lStan->AutoSize = true;
			this->lStan->Location = System::Drawing::Point(310, 327);
			this->lStan->MinimumSize = System::Drawing::Size(120, 0);
			this->lStan->Name = L"lStan";
			this->lStan->Size = System::Drawing::Size(120, 13);
			this->lStan->TabIndex = 27;
			this->lStan->Text = L"...";
			this->lStan->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// aplikacja
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(669, 450);
			this->Controls->Add(this->lStan);
			this->Controls->Add(this->tWywolania);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->lCzas);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->pictureBox6);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->lWatki);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->trackBar);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->tSciezka);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Name = L"aplikacja";
			this->Text = L"Multifiltr";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		this->lStan->Text = (L"Przetwarzanie");
		std::string plik = marshal_as<std::string>(this->tSciezka->Text);
		int watki = this->trackBar->Value;

		char kod;
		if (this->radioASM->Checked)
			kod = 'a';
		else
			kod = 'c';

		int wywolania = int::Parse(this->tWywolania->Text);

		double wynik = przetworz("img\\lexus.bmp", 'a', 1, 1);
		//double wynik = przetworz(plik, kod, wywolania,this->trackBar->Value);
		if (wynik == -1)
		{
			this->lStan->Text = (L"B³¹d otwierania pliku");
		}
		else if (wynik == -2)
		{
			this->lStan->Text = (L"B³¹d zapisu pliku");
		}
		else
		{
			this->lStan->Text = (L"Gotowe");
			this->pictureBox1->BackgroundImage = Image::FromFile("img\\lexus.bmp");
			//this->pictureBox1->BackgroundImage = Image::FromFile(this->tSciezka->Text);
			this->pictureBox2->BackgroundImage = Image::FromFile(L"img\\SZARY.bmp");
			this->pictureBox3->BackgroundImage = Image::FromFile(L"img\\SEPIA.bmp");
			this->pictureBox4->BackgroundImage = Image::FromFile(L"img\\KONTR.bmp");
			this->pictureBox5->BackgroundImage = Image::FromFile(L"img\\SOLAR.bmp");
			this->pictureBox6->BackgroundImage = Image::FromFile(L"img\\GAUSS.bmp");
			//this->button1->Visible = false;
			this->lCzas->Text = wynik.ToString();
		}
	}
	private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e) 
	{
		this->lWatki->Text = this->trackBar->Value.ToString();
	}
};
}
