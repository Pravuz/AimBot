#pragma once
#define __DESKTOP

#include "Aimbot_Serial.h"
#include "Form2.h"

namespace AimbotC {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Main
	/// </summary>
	public ref class Main : public System::Windows::Forms::Form
	{
	public:
		
		AimBot_Serial^ m_serial;
		
		Main(void)
		{	
			InitializeComponent();
			m_serial = gcnew AimBot_Serial(serialPort);
			//
			//TODO: Add the constructor code here
			//
			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::IO::Ports::SerialPort^  serialPort;
	private: System::Windows::Forms::ComboBox^  cboPorts;
	private: System::Windows::Forms::Button^  btnClose;

	private: System::Windows::Forms::Button^  btnOpen;


	private: System::Windows::Forms::Label^  lblStatus;

	private: System::Windows::Forms::Button^  btnRefresh;
	private: System::Windows::Forms::Button^  btnGetSettings;

	private: System::Windows::Forms::CheckBox^  chkIsDSLR;

	private: System::Windows::Forms::Label^  lblCam_Btn_Delay;
	private: System::Windows::Forms::Label^  lblCam_Trigger_Delay;
	private: System::Windows::Forms::Label^  lblCam_Focus_Delay;
	private: System::Windows::Forms::Label^  lblloop_Time;

	private: System::Windows::Forms::Label^  lblXRcMin;
	private: System::Windows::Forms::Label^  lblXRcMax;
	private: System::Windows::Forms::Label^  lblXVect_InMin;

	private: System::Windows::Forms::Label^  lblYRcMapMax;

	private: System::Windows::Forms::Label^  lblYRcMapMin;

	private: System::Windows::Forms::Label^  lblYRcMax;

	private: System::Windows::Forms::Label^  lblYRcMin;

	private: System::Windows::Forms::Label^  lblRcMapMax;

	private: System::Windows::Forms::Label^  lblXRcMapMax;
private: System::Windows::Forms::Label^  lblYVect_OutMax;


private: System::Windows::Forms::Label^  lblYVect_OutMin;

private: System::Windows::Forms::Label^  lblYVect_InMax;

private: System::Windows::Forms::Label^  lblYVect_InMin;

private: System::Windows::Forms::Label^  lblXVect_OutMax;

private: System::Windows::Forms::Label^  lblXVect_OutMin;

private: System::Windows::Forms::Label^  lblXVectt_InMax;
private: System::Windows::Forms::Button^  btnSaveSettings;
private: System::Windows::Forms::Button^  btnSaveToEEPROM;
	private: System::Windows::Forms::Button^  btnDefaults;


private: System::Windows::Forms::NumericUpDown^  numCam_Trigger_Delay;
private: System::Windows::Forms::NumericUpDown^  numCam_Focus_Delay;
private: System::Windows::Forms::NumericUpDown^  numLoop_Time;
private: System::Windows::Forms::NumericUpDown^  numCam_Btn_Delay;
private: System::Windows::Forms::NumericUpDown^  numXRcMin;
private: System::Windows::Forms::NumericUpDown^  numXRcMax;
private: System::Windows::Forms::NumericUpDown^  numXRcMapMin;
private: System::Windows::Forms::NumericUpDown^  numXRcMapMax;
private: System::Windows::Forms::NumericUpDown^  numYRcMin;
private: System::Windows::Forms::NumericUpDown^  numYRcMax;
private: System::Windows::Forms::NumericUpDown^  numYRcMapMin;
private: System::Windows::Forms::NumericUpDown^  numYRcMapMax;
private: System::Windows::Forms::NumericUpDown^  numXVect_InMin;
private: System::Windows::Forms::NumericUpDown^  numXVect_InMax;
private: System::Windows::Forms::NumericUpDown^  numXVect_OutMin;
private: System::Windows::Forms::NumericUpDown^  numXVect_OutMax;
private: System::Windows::Forms::NumericUpDown^  numYVect_InMin;
private: System::Windows::Forms::NumericUpDown^  numYVect_InMax;
private: System::Windows::Forms::NumericUpDown^  numYVect_OutMin;
private: System::Windows::Forms::NumericUpDown^  numYVect_OutMax;
private: System::Windows::Forms::PictureBox^  pbxStatus;

private: System::Windows::Forms::TextBox^  txtGeneral;
private: System::Windows::Forms::TextBox^  txtRC;
private: System::Windows::Forms::TextBox^  txtVector;













private: System::Windows::Forms::Panel^  pnlVector;


private: System::Windows::Forms::Panel^  pnlRC;

private: System::Windows::Forms::Panel^  pnlGeneral;
private: System::Windows::Forms::Panel^  pnlBack;



private: System::Windows::Forms::Label^  lblV;
private: System::Windows::Forms::TextBox^  txtHelp;








	protected:

	protected:
	private: System::ComponentModel::IContainer^  components;

	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Main::typeid));
			this->serialPort = (gcnew System::IO::Ports::SerialPort(this->components));
			this->cboPorts = (gcnew System::Windows::Forms::ComboBox());
			this->btnClose = (gcnew System::Windows::Forms::Button());
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->lblStatus = (gcnew System::Windows::Forms::Label());
			this->btnRefresh = (gcnew System::Windows::Forms::Button());
			this->btnGetSettings = (gcnew System::Windows::Forms::Button());
			this->chkIsDSLR = (gcnew System::Windows::Forms::CheckBox());
			this->lblCam_Btn_Delay = (gcnew System::Windows::Forms::Label());
			this->lblCam_Trigger_Delay = (gcnew System::Windows::Forms::Label());
			this->lblCam_Focus_Delay = (gcnew System::Windows::Forms::Label());
			this->lblloop_Time = (gcnew System::Windows::Forms::Label());
			this->lblXRcMin = (gcnew System::Windows::Forms::Label());
			this->lblXRcMax = (gcnew System::Windows::Forms::Label());
			this->lblXVect_InMin = (gcnew System::Windows::Forms::Label());
			this->lblYRcMapMax = (gcnew System::Windows::Forms::Label());
			this->lblYRcMapMin = (gcnew System::Windows::Forms::Label());
			this->lblYRcMax = (gcnew System::Windows::Forms::Label());
			this->lblYRcMin = (gcnew System::Windows::Forms::Label());
			this->lblRcMapMax = (gcnew System::Windows::Forms::Label());
			this->lblXRcMapMax = (gcnew System::Windows::Forms::Label());
			this->lblYVect_OutMax = (gcnew System::Windows::Forms::Label());
			this->lblYVect_OutMin = (gcnew System::Windows::Forms::Label());
			this->lblYVect_InMax = (gcnew System::Windows::Forms::Label());
			this->lblYVect_InMin = (gcnew System::Windows::Forms::Label());
			this->lblXVect_OutMax = (gcnew System::Windows::Forms::Label());
			this->lblXVect_OutMin = (gcnew System::Windows::Forms::Label());
			this->lblXVectt_InMax = (gcnew System::Windows::Forms::Label());
			this->btnSaveSettings = (gcnew System::Windows::Forms::Button());
			this->btnSaveToEEPROM = (gcnew System::Windows::Forms::Button());
			this->btnDefaults = (gcnew System::Windows::Forms::Button());
			this->numCam_Trigger_Delay = (gcnew System::Windows::Forms::NumericUpDown());
			this->numCam_Focus_Delay = (gcnew System::Windows::Forms::NumericUpDown());
			this->numLoop_Time = (gcnew System::Windows::Forms::NumericUpDown());
			this->numCam_Btn_Delay = (gcnew System::Windows::Forms::NumericUpDown());
			this->numXRcMin = (gcnew System::Windows::Forms::NumericUpDown());
			this->numXRcMax = (gcnew System::Windows::Forms::NumericUpDown());
			this->numXRcMapMin = (gcnew System::Windows::Forms::NumericUpDown());
			this->numXRcMapMax = (gcnew System::Windows::Forms::NumericUpDown());
			this->numYRcMin = (gcnew System::Windows::Forms::NumericUpDown());
			this->numYRcMax = (gcnew System::Windows::Forms::NumericUpDown());
			this->numYRcMapMin = (gcnew System::Windows::Forms::NumericUpDown());
			this->numYRcMapMax = (gcnew System::Windows::Forms::NumericUpDown());
			this->numXVect_InMin = (gcnew System::Windows::Forms::NumericUpDown());
			this->numXVect_InMax = (gcnew System::Windows::Forms::NumericUpDown());
			this->numXVect_OutMin = (gcnew System::Windows::Forms::NumericUpDown());
			this->numXVect_OutMax = (gcnew System::Windows::Forms::NumericUpDown());
			this->numYVect_InMin = (gcnew System::Windows::Forms::NumericUpDown());
			this->numYVect_InMax = (gcnew System::Windows::Forms::NumericUpDown());
			this->numYVect_OutMin = (gcnew System::Windows::Forms::NumericUpDown());
			this->numYVect_OutMax = (gcnew System::Windows::Forms::NumericUpDown());
			this->pbxStatus = (gcnew System::Windows::Forms::PictureBox());
			this->txtGeneral = (gcnew System::Windows::Forms::TextBox());
			this->txtRC = (gcnew System::Windows::Forms::TextBox());
			this->txtVector = (gcnew System::Windows::Forms::TextBox());
			this->pnlVector = (gcnew System::Windows::Forms::Panel());
			this->pnlRC = (gcnew System::Windows::Forms::Panel());
			this->pnlGeneral = (gcnew System::Windows::Forms::Panel());
			this->pnlBack = (gcnew System::Windows::Forms::Panel());
			this->lblV = (gcnew System::Windows::Forms::Label());
			this->txtHelp = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numCam_Trigger_Delay))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numCam_Focus_Delay))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numLoop_Time))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numCam_Btn_Delay))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numXRcMin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numXRcMax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numXRcMapMin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numXRcMapMax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numYRcMin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numYRcMax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numYRcMapMin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numYRcMapMax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numXVect_InMin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numXVect_InMax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numXVect_OutMin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numXVect_OutMax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numYVect_InMin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numYVect_InMax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numYVect_OutMin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numYVect_OutMax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbxStatus))->BeginInit();
			this->pnlBack->SuspendLayout();
			this->SuspendLayout();
			// 
			// serialPort
			// 
			this->serialPort->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &Main::serialPort_DataRecived);
			// 
			// cboPorts
			// 
			this->cboPorts->BackColor = System::Drawing::Color::White;
			this->cboPorts->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboPorts->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cboPorts->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cboPorts->FormattingEnabled = true;
			this->cboPorts->Location = System::Drawing::Point(15, 14);
			this->cboPorts->Name = L"cboPorts";
			this->cboPorts->Size = System::Drawing::Size(92, 24);
			this->cboPorts->TabIndex = 27;
			// 
			// btnClose
			// 
			this->btnClose->BackColor = System::Drawing::Color::Firebrick;
			this->btnClose->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnClose->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnClose->ForeColor = System::Drawing::Color::White;
			this->btnClose->Location = System::Drawing::Point(193, 15);
			this->btnClose->Name = L"btnClose";
			this->btnClose->Size = System::Drawing::Size(92, 24);
			this->btnClose->TabIndex = 1;
			this->btnClose->Text = L"Close Port";
			this->btnClose->UseVisualStyleBackColor = false;
			this->btnClose->Click += gcnew System::EventHandler(this, &Main::btnClose_Click);
			// 
			// btnOpen
			// 
			this->btnOpen->BackColor = System::Drawing::Color::Green;
			this->btnOpen->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnOpen->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnOpen->ForeColor = System::Drawing::Color::White;
			this->btnOpen->Location = System::Drawing::Point(193, 15);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(92, 24);
			this->btnOpen->TabIndex = 29;
			this->btnOpen->Text = L"Open Port";
			this->btnOpen->UseVisualStyleBackColor = false;
			this->btnOpen->Click += gcnew System::EventHandler(this, &Main::btnOpen_Click);
			// 
			// lblStatus
			// 
			this->lblStatus->AutoSize = true;
			this->lblStatus->BackColor = System::Drawing::Color::Firebrick;
			this->lblStatus->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStatus->ForeColor = System::Drawing::Color::White;
			this->lblStatus->Location = System::Drawing::Point(274, 515);
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(116, 17);
			this->lblStatus->TabIndex = 6;
			this->lblStatus->Text = L"Not Connected";
			this->lblStatus->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btnRefresh
			// 
			this->btnRefresh->BackColor = System::Drawing::Color::DarkOrange;
			this->btnRefresh->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->btnRefresh->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnRefresh->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRefresh->ForeColor = System::Drawing::Color::White;
			this->btnRefresh->Location = System::Drawing::Point(113, 15);
			this->btnRefresh->Name = L"btnRefresh";
			this->btnRefresh->Size = System::Drawing::Size(74, 22);
			this->btnRefresh->TabIndex = 28;
			this->btnRefresh->Text = L"Refresh";
			this->btnRefresh->UseVisualStyleBackColor = false;
			this->btnRefresh->Click += gcnew System::EventHandler(this, &Main::btnRefresh_Click);
			// 
			// btnGetSettings
			// 
			this->btnGetSettings->BackColor = System::Drawing::Color::DarkOrange;
			this->btnGetSettings->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnGetSettings->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnGetSettings->ForeColor = System::Drawing::Color::Transparent;
			this->btnGetSettings->Location = System::Drawing::Point(134, 413);
			this->btnGetSettings->Name = L"btnGetSettings";
			this->btnGetSettings->Size = System::Drawing::Size(134, 22);
			this->btnGetSettings->TabIndex = 24;
			this->btnGetSettings->Text = L"Get Current";
			this->btnGetSettings->UseVisualStyleBackColor = false;
			this->btnGetSettings->Click += gcnew System::EventHandler(this, &Main::btnSend_Click);
			// 
			// chkIsDSLR
			// 
			this->chkIsDSLR->AutoSize = true;
			this->chkIsDSLR->BackColor = System::Drawing::Color::White;
			this->chkIsDSLR->Font = (gcnew System::Drawing::Font(L"Helonia", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->chkIsDSLR->Location = System::Drawing::Point(21, 46);
			this->chkIsDSLR->Name = L"chkIsDSLR";
			this->chkIsDSLR->Size = System::Drawing::Size(61, 20);
			this->chkIsDSLR->TabIndex = 0;
			this->chkIsDSLR->Text = L"DSLR";
			this->chkIsDSLR->UseVisualStyleBackColor = false;
			this->chkIsDSLR->MouseHover += gcnew System::EventHandler(this, &Main::chkIsDSLR_MouseHover);
			// 
			// lblCam_Btn_Delay
			// 
			this->lblCam_Btn_Delay->AutoSize = true;
			this->lblCam_Btn_Delay->BackColor = System::Drawing::Color::White;
			this->lblCam_Btn_Delay->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblCam_Btn_Delay->Location = System::Drawing::Point(100, 87);
			this->lblCam_Btn_Delay->Name = L"lblCam_Btn_Delay";
			this->lblCam_Btn_Delay->Size = System::Drawing::Size(126, 17);
			this->lblCam_Btn_Delay->TabIndex = 34;
			this->lblCam_Btn_Delay->Text = L"Camera Button Delay";
			this->lblCam_Btn_Delay->MouseHover += gcnew System::EventHandler(this, &Main::lblCam_Btn_Delay_MouseHover);
			// 
			// lblCam_Trigger_Delay
			// 
			this->lblCam_Trigger_Delay->AutoSize = true;
			this->lblCam_Trigger_Delay->BackColor = System::Drawing::Color::White;
			this->lblCam_Trigger_Delay->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblCam_Trigger_Delay->Location = System::Drawing::Point(100, 132);
			this->lblCam_Trigger_Delay->Name = L"lblCam_Trigger_Delay";
			this->lblCam_Trigger_Delay->Size = System::Drawing::Size(127, 17);
			this->lblCam_Trigger_Delay->TabIndex = 35;
			this->lblCam_Trigger_Delay->Text = L"Camera Trigger Delay";
			this->lblCam_Trigger_Delay->MouseHover += gcnew System::EventHandler(this, &Main::lblCam_Trigger_Delay_MouseHover);
			// 
			// lblCam_Focus_Delay
			// 
			this->lblCam_Focus_Delay->AutoSize = true;
			this->lblCam_Focus_Delay->BackColor = System::Drawing::Color::White;
			this->lblCam_Focus_Delay->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblCam_Focus_Delay->Location = System::Drawing::Point(100, 177);
			this->lblCam_Focus_Delay->Name = L"lblCam_Focus_Delay";
			this->lblCam_Focus_Delay->Size = System::Drawing::Size(122, 17);
			this->lblCam_Focus_Delay->TabIndex = 36;
			this->lblCam_Focus_Delay->Text = L"Camera Focus Delay";
			this->lblCam_Focus_Delay->MouseHover += gcnew System::EventHandler(this, &Main::lblCam_Focus_Delay_MouseHover);
			// 
			// lblloop_Time
			// 
			this->lblloop_Time->AutoSize = true;
			this->lblloop_Time->BackColor = System::Drawing::Color::White;
			this->lblloop_Time->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblloop_Time->Location = System::Drawing::Point(100, 221);
			this->lblloop_Time->Name = L"lblloop_Time";
			this->lblloop_Time->Size = System::Drawing::Size(65, 17);
			this->lblloop_Time->TabIndex = 37;
			this->lblloop_Time->Text = L"Loop Time";
			this->lblloop_Time->MouseHover += gcnew System::EventHandler(this, &Main::lblloop_Time_MouseHover);
			// 
			// lblXRcMin
			// 
			this->lblXRcMin->AutoSize = true;
			this->lblXRcMin->BackColor = System::Drawing::Color::White;
			this->lblXRcMin->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblXRcMin->Location = System::Drawing::Point(377, 91);
			this->lblXRcMin->Name = L"lblXRcMin";
			this->lblXRcMin->Size = System::Drawing::Size(55, 17);
			this->lblXRcMin->TabIndex = 36;
			this->lblXRcMin->Text = L"X Rc Min";
			this->lblXRcMin->MouseHover += gcnew System::EventHandler(this, &Main::lblXRcMin_MouseHover);
			// 
			// lblXRcMax
			// 
			this->lblXRcMax->AutoSize = true;
			this->lblXRcMax->BackColor = System::Drawing::Color::White;
			this->lblXRcMax->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblXRcMax->Location = System::Drawing::Point(377, 115);
			this->lblXRcMax->Name = L"lblXRcMax";
			this->lblXRcMax->Size = System::Drawing::Size(57, 17);
			this->lblXRcMax->TabIndex = 148;
			this->lblXRcMax->Text = L"X Rc Max";
			this->lblXRcMax->MouseHover += gcnew System::EventHandler(this, &Main::lblXRcMax_MouseHover);
			// 
			// lblXVect_InMin
			// 
			this->lblXVect_InMin->AutoSize = true;
			this->lblXVect_InMin->BackColor = System::Drawing::Color::White;
			this->lblXVect_InMin->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblXVect_InMin->Location = System::Drawing::Point(377, 267);
			this->lblXVect_InMin->Name = L"lblXVect_InMin";
			this->lblXVect_InMin->Size = System::Drawing::Size(89, 17);
			this->lblXVect_InMin->TabIndex = 47;
			this->lblXVect_InMin->Text = L"X Vector In Min";
			this->lblXVect_InMin->MouseHover += gcnew System::EventHandler(this, &Main::lblXVect_InMin_MouseHover);
			// 
			// lblYRcMapMax
			// 
			this->lblYRcMapMax->AutoSize = true;
			this->lblYRcMapMax->BackColor = System::Drawing::Color::White;
			this->lblYRcMapMax->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblYRcMapMax->Location = System::Drawing::Point(558, 169);
			this->lblYRcMapMax->Name = L"lblYRcMapMax";
			this->lblYRcMapMax->Size = System::Drawing::Size(84, 17);
			this->lblYRcMapMax->TabIndex = 46;
			this->lblYRcMapMax->Text = L"Y Rc Map Max";
			this->lblYRcMapMax->MouseHover += gcnew System::EventHandler(this, &Main::lblYRcMapMax_MouseHover);
			// 
			// lblYRcMapMin
			// 
			this->lblYRcMapMin->AutoSize = true;
			this->lblYRcMapMin->BackColor = System::Drawing::Color::White;
			this->lblYRcMapMin->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblYRcMapMin->Location = System::Drawing::Point(558, 143);
			this->lblYRcMapMin->Name = L"lblYRcMapMin";
			this->lblYRcMapMin->Size = System::Drawing::Size(82, 17);
			this->lblYRcMapMin->TabIndex = 45;
			this->lblYRcMapMin->Text = L"Y Rc Map Min";
			this->lblYRcMapMin->MouseHover += gcnew System::EventHandler(this, &Main::lblYRcMapMin_MouseHover);
			// 
			// lblYRcMax
			// 
			this->lblYRcMax->AutoSize = true;
			this->lblYRcMax->BackColor = System::Drawing::Color::White;
			this->lblYRcMax->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblYRcMax->Location = System::Drawing::Point(558, 117);
			this->lblYRcMax->Name = L"lblYRcMax";
			this->lblYRcMax->Size = System::Drawing::Size(57, 17);
			this->lblYRcMax->TabIndex = 44;
			this->lblYRcMax->Text = L"Y Rc Max";
			this->lblYRcMax->MouseHover += gcnew System::EventHandler(this, &Main::lblYRcMax_MouseHover);
			// 
			// lblYRcMin
			// 
			this->lblYRcMin->AutoSize = true;
			this->lblYRcMin->BackColor = System::Drawing::Color::White;
			this->lblYRcMin->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblYRcMin->Location = System::Drawing::Point(558, 92);
			this->lblYRcMin->Name = L"lblYRcMin";
			this->lblYRcMin->Size = System::Drawing::Size(55, 17);
			this->lblYRcMin->TabIndex = 43;
			this->lblYRcMin->Text = L"Y Rc Min";
			this->lblYRcMin->MouseHover += gcnew System::EventHandler(this, &Main::lblYRcMin_MouseHover);
			// 
			// lblRcMapMax
			// 
			this->lblRcMapMax->AutoSize = true;
			this->lblRcMapMax->BackColor = System::Drawing::Color::White;
			this->lblRcMapMax->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRcMapMax->Location = System::Drawing::Point(377, 167);
			this->lblRcMapMax->Name = L"lblRcMapMax";
			this->lblRcMapMax->Size = System::Drawing::Size(84, 17);
			this->lblRcMapMax->TabIndex = 42;
			this->lblRcMapMax->Text = L"X Rc Map Max";
			this->lblRcMapMax->MouseHover += gcnew System::EventHandler(this, &Main::lblRcMapMax_MouseHover);
			// 
			// lblXRcMapMax
			// 
			this->lblXRcMapMax->AutoSize = true;
			this->lblXRcMapMax->BackColor = System::Drawing::Color::White;
			this->lblXRcMapMax->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblXRcMapMax->Location = System::Drawing::Point(377, 141);
			this->lblXRcMapMax->Name = L"lblXRcMapMax";
			this->lblXRcMapMax->Size = System::Drawing::Size(82, 17);
			this->lblXRcMapMax->TabIndex = 198;
			this->lblXRcMapMax->Text = L"X Rc Map Min";
			this->lblXRcMapMax->MouseHover += gcnew System::EventHandler(this, &Main::lblXRcMapMax_MouseHover);
			// 
			// lblYVect_OutMax
			// 
			this->lblYVect_OutMax->AutoSize = true;
			this->lblYVect_OutMax->BackColor = System::Drawing::Color::White;
			this->lblYVect_OutMax->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblYVect_OutMax->Location = System::Drawing::Point(558, 345);
			this->lblYVect_OutMax->Name = L"lblYVect_OutMax";
			this->lblYVect_OutMax->Size = System::Drawing::Size(100, 17);
			this->lblYVect_OutMax->TabIndex = 54;
			this->lblYVect_OutMax->Text = L"Y Vector Out Max";
			this->lblYVect_OutMax->MouseHover += gcnew System::EventHandler(this, &Main::lblYVect_OutMax_MouseHover);
			// 
			// lblYVect_OutMin
			// 
			this->lblYVect_OutMin->AutoSize = true;
			this->lblYVect_OutMin->BackColor = System::Drawing::Color::White;
			this->lblYVect_OutMin->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblYVect_OutMin->Location = System::Drawing::Point(558, 319);
			this->lblYVect_OutMin->Name = L"lblYVect_OutMin";
			this->lblYVect_OutMin->Size = System::Drawing::Size(98, 17);
			this->lblYVect_OutMin->TabIndex = 53;
			this->lblYVect_OutMin->Text = L"Y Vector Out Min";
			this->lblYVect_OutMin->MouseHover += gcnew System::EventHandler(this, &Main::lblYVect_OutMin_MouseHover);
			// 
			// lblYVect_InMax
			// 
			this->lblYVect_InMax->AutoSize = true;
			this->lblYVect_InMax->BackColor = System::Drawing::Color::White;
			this->lblYVect_InMax->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblYVect_InMax->Location = System::Drawing::Point(558, 293);
			this->lblYVect_InMax->Name = L"lblYVect_InMax";
			this->lblYVect_InMax->Size = System::Drawing::Size(91, 17);
			this->lblYVect_InMax->TabIndex = 52;
			this->lblYVect_InMax->Text = L"Y Vector In Max";
			this->lblYVect_InMax->MouseHover += gcnew System::EventHandler(this, &Main::lblYVect_InMax_MouseHover);
			// 
			// lblYVect_InMin
			// 
			this->lblYVect_InMin->AutoSize = true;
			this->lblYVect_InMin->BackColor = System::Drawing::Color::White;
			this->lblYVect_InMin->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblYVect_InMin->Location = System::Drawing::Point(558, 267);
			this->lblYVect_InMin->Name = L"lblYVect_InMin";
			this->lblYVect_InMin->Size = System::Drawing::Size(89, 17);
			this->lblYVect_InMin->TabIndex = 51;
			this->lblYVect_InMin->Text = L"Y Vector In Min";
			this->lblYVect_InMin->MouseHover += gcnew System::EventHandler(this, &Main::lblYVect_InMin_MouseHover);
			// 
			// lblXVect_OutMax
			// 
			this->lblXVect_OutMax->AutoSize = true;
			this->lblXVect_OutMax->BackColor = System::Drawing::Color::White;
			this->lblXVect_OutMax->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblXVect_OutMax->Location = System::Drawing::Point(377, 345);
			this->lblXVect_OutMax->Name = L"lblXVect_OutMax";
			this->lblXVect_OutMax->Size = System::Drawing::Size(100, 17);
			this->lblXVect_OutMax->TabIndex = 50;
			this->lblXVect_OutMax->Text = L"X Vector Out Max";
			this->lblXVect_OutMax->MouseHover += gcnew System::EventHandler(this, &Main::lblXVect_OutMax_MouseHover);
			// 
			// lblXVect_OutMin
			// 
			this->lblXVect_OutMin->AutoSize = true;
			this->lblXVect_OutMin->BackColor = System::Drawing::Color::White;
			this->lblXVect_OutMin->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblXVect_OutMin->Location = System::Drawing::Point(377, 319);
			this->lblXVect_OutMin->Name = L"lblXVect_OutMin";
			this->lblXVect_OutMin->Size = System::Drawing::Size(98, 17);
			this->lblXVect_OutMin->TabIndex = 49;
			this->lblXVect_OutMin->Text = L"X Vector Out Min";
			this->lblXVect_OutMin->MouseHover += gcnew System::EventHandler(this, &Main::lblXVect_OutMin_MouseHover);
			// 
			// lblXVectt_InMax
			// 
			this->lblXVectt_InMax->AutoSize = true;
			this->lblXVectt_InMax->BackColor = System::Drawing::Color::White;
			this->lblXVectt_InMax->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblXVectt_InMax->Location = System::Drawing::Point(377, 293);
			this->lblXVectt_InMax->Name = L"lblXVectt_InMax";
			this->lblXVectt_InMax->Size = System::Drawing::Size(91, 17);
			this->lblXVectt_InMax->TabIndex = 48;
			this->lblXVectt_InMax->Text = L"X Vector In Max";
			this->lblXVectt_InMax->MouseHover += gcnew System::EventHandler(this, &Main::lblXVectt_InMax_MouseHover);
			// 
			// btnSaveSettings
			// 
			this->btnSaveSettings->BackColor = System::Drawing::Color::DarkOrange;
			this->btnSaveSettings->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnSaveSettings->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnSaveSettings->ForeColor = System::Drawing::Color::Transparent;
			this->btnSaveSettings->Location = System::Drawing::Point(274, 413);
			this->btnSaveSettings->Name = L"btnSaveSettings";
			this->btnSaveSettings->Size = System::Drawing::Size(134, 22);
			this->btnSaveSettings->TabIndex = 25;
			this->btnSaveSettings->Text = L"Upload Settings";
			this->btnSaveSettings->UseVisualStyleBackColor = false;
			this->btnSaveSettings->Click += gcnew System::EventHandler(this, &Main::btnSaveSettings_Click);
			// 
			// btnSaveToEEPROM
			// 
			this->btnSaveToEEPROM->BackColor = System::Drawing::Color::DarkOrange;
			this->btnSaveToEEPROM->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnSaveToEEPROM->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnSaveToEEPROM->ForeColor = System::Drawing::Color::Transparent;
			this->btnSaveToEEPROM->Location = System::Drawing::Point(415, 413);
			this->btnSaveToEEPROM->Name = L"btnSaveToEEPROM";
			this->btnSaveToEEPROM->Size = System::Drawing::Size(134, 22);
			this->btnSaveToEEPROM->TabIndex = 26;
			this->btnSaveToEEPROM->Text = L"Save to EEPROM";
			this->btnSaveToEEPROM->UseVisualStyleBackColor = false;
			this->btnSaveToEEPROM->Click += gcnew System::EventHandler(this, &Main::btnSaveToEEPROM_Click);
			// 
			// btnDefaults
			// 
			this->btnDefaults->BackColor = System::Drawing::Color::RoyalBlue;
			this->btnDefaults->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnDefaults->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDefaults->ForeColor = System::Drawing::Color::White;
			this->btnDefaults->Location = System::Drawing::Point(599, 435);
			this->btnDefaults->Name = L"btnDefaults";
			this->btnDefaults->Size = System::Drawing::Size(70, 22);
			this->btnDefaults->TabIndex = 57;
			this->btnDefaults->Text = L"Defaults";
			this->btnDefaults->UseVisualStyleBackColor = false;
			this->btnDefaults->Click += gcnew System::EventHandler(this, &Main::button1_Click);
			// 
			// numCam_Trigger_Delay
			// 
			this->numCam_Trigger_Delay->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numCam_Trigger_Delay->Location = System::Drawing::Point(21, 130);
			this->numCam_Trigger_Delay->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numCam_Trigger_Delay->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numCam_Trigger_Delay->Name = L"numCam_Trigger_Delay";
			this->numCam_Trigger_Delay->Size = System::Drawing::Size(73, 22);
			this->numCam_Trigger_Delay->TabIndex = 2;
			// 
			// numCam_Focus_Delay
			// 
			this->numCam_Focus_Delay->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numCam_Focus_Delay->Location = System::Drawing::Point(21, 175);
			this->numCam_Focus_Delay->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numCam_Focus_Delay->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numCam_Focus_Delay->Name = L"numCam_Focus_Delay";
			this->numCam_Focus_Delay->Size = System::Drawing::Size(73, 22);
			this->numCam_Focus_Delay->TabIndex = 3;
			// 
			// numLoop_Time
			// 
			this->numLoop_Time->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numLoop_Time->Location = System::Drawing::Point(21, 219);
			this->numLoop_Time->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numLoop_Time->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numLoop_Time->Name = L"numLoop_Time";
			this->numLoop_Time->Size = System::Drawing::Size(73, 22);
			this->numLoop_Time->TabIndex = 4;
			// 
			// numCam_Btn_Delay
			// 
			this->numCam_Btn_Delay->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numCam_Btn_Delay->Location = System::Drawing::Point(21, 85);
			this->numCam_Btn_Delay->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numCam_Btn_Delay->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numCam_Btn_Delay->Name = L"numCam_Btn_Delay";
			this->numCam_Btn_Delay->Size = System::Drawing::Size(73, 22);
			this->numCam_Btn_Delay->TabIndex = 1;
			// 
			// numXRcMin
			// 
			this->numXRcMin->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numXRcMin->Location = System::Drawing::Point(298, 87);
			this->numXRcMin->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numXRcMin->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numXRcMin->Name = L"numXRcMin";
			this->numXRcMin->Size = System::Drawing::Size(73, 22);
			this->numXRcMin->TabIndex = 5;
			// 
			// numXRcMax
			// 
			this->numXRcMax->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numXRcMax->Location = System::Drawing::Point(298, 112);
			this->numXRcMax->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numXRcMax->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numXRcMax->Name = L"numXRcMax";
			this->numXRcMax->Size = System::Drawing::Size(73, 22);
			this->numXRcMax->TabIndex = 6;
			// 
			// numXRcMapMin
			// 
			this->numXRcMapMin->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numXRcMapMin->Location = System::Drawing::Point(298, 138);
			this->numXRcMapMin->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numXRcMapMin->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numXRcMapMin->Name = L"numXRcMapMin";
			this->numXRcMapMin->Size = System::Drawing::Size(73, 22);
			this->numXRcMapMin->TabIndex = 7;
			// 
			// numXRcMapMax
			// 
			this->numXRcMapMax->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numXRcMapMax->Location = System::Drawing::Point(298, 165);
			this->numXRcMapMax->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numXRcMapMax->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numXRcMapMax->Name = L"numXRcMapMax";
			this->numXRcMapMax->Size = System::Drawing::Size(73, 22);
			this->numXRcMapMax->TabIndex = 8;
			// 
			// numYRcMin
			// 
			this->numYRcMin->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numYRcMin->Location = System::Drawing::Point(479, 89);
			this->numYRcMin->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numYRcMin->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numYRcMin->Name = L"numYRcMin";
			this->numYRcMin->Size = System::Drawing::Size(73, 22);
			this->numYRcMin->TabIndex = 9;
			// 
			// numYRcMax
			// 
			this->numYRcMax->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numYRcMax->Location = System::Drawing::Point(479, 115);
			this->numYRcMax->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numYRcMax->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numYRcMax->Name = L"numYRcMax";
			this->numYRcMax->Size = System::Drawing::Size(73, 22);
			this->numYRcMax->TabIndex = 10;
			// 
			// numYRcMapMin
			// 
			this->numYRcMapMin->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numYRcMapMin->Location = System::Drawing::Point(479, 140);
			this->numYRcMapMin->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numYRcMapMin->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numYRcMapMin->Name = L"numYRcMapMin";
			this->numYRcMapMin->Size = System::Drawing::Size(73, 22);
			this->numYRcMapMin->TabIndex = 11;
			// 
			// numYRcMapMax
			// 
			this->numYRcMapMax->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numYRcMapMax->Location = System::Drawing::Point(479, 166);
			this->numYRcMapMax->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numYRcMapMax->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numYRcMapMax->Name = L"numYRcMapMax";
			this->numYRcMapMax->Size = System::Drawing::Size(73, 22);
			this->numYRcMapMax->TabIndex = 12;
			// 
			// numXVect_InMin
			// 
			this->numXVect_InMin->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numXVect_InMin->Location = System::Drawing::Point(298, 265);
			this->numXVect_InMin->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numXVect_InMin->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, System::Int32::MinValue });
			this->numXVect_InMin->Name = L"numXVect_InMin";
			this->numXVect_InMin->Size = System::Drawing::Size(73, 22);
			this->numXVect_InMin->TabIndex = 16;
			// 
			// numXVect_InMax
			// 
			this->numXVect_InMax->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numXVect_InMax->Location = System::Drawing::Point(298, 291);
			this->numXVect_InMax->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numXVect_InMax->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numXVect_InMax->Name = L"numXVect_InMax";
			this->numXVect_InMax->Size = System::Drawing::Size(73, 22);
			this->numXVect_InMax->TabIndex = 17;
			// 
			// numXVect_OutMin
			// 
			this->numXVect_OutMin->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numXVect_OutMin->Location = System::Drawing::Point(298, 317);
			this->numXVect_OutMin->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numXVect_OutMin->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numXVect_OutMin->Name = L"numXVect_OutMin";
			this->numXVect_OutMin->Size = System::Drawing::Size(73, 22);
			this->numXVect_OutMin->TabIndex = 18;
			// 
			// numXVect_OutMax
			// 
			this->numXVect_OutMax->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numXVect_OutMax->Location = System::Drawing::Point(298, 343);
			this->numXVect_OutMax->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numXVect_OutMax->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numXVect_OutMax->Name = L"numXVect_OutMax";
			this->numXVect_OutMax->Size = System::Drawing::Size(73, 22);
			this->numXVect_OutMax->TabIndex = 19;
			// 
			// numYVect_InMin
			// 
			this->numYVect_InMin->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numYVect_InMin->Location = System::Drawing::Point(479, 265);
			this->numYVect_InMin->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numYVect_InMin->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 300, 0, 0, System::Int32::MinValue });
			this->numYVect_InMin->Name = L"numYVect_InMin";
			this->numYVect_InMin->Size = System::Drawing::Size(73, 22);
			this->numYVect_InMin->TabIndex = 20;
			// 
			// numYVect_InMax
			// 
			this->numYVect_InMax->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numYVect_InMax->Location = System::Drawing::Point(479, 291);
			this->numYVect_InMax->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numYVect_InMax->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numYVect_InMax->Name = L"numYVect_InMax";
			this->numYVect_InMax->Size = System::Drawing::Size(73, 22);
			this->numYVect_InMax->TabIndex = 21;
			// 
			// numYVect_OutMin
			// 
			this->numYVect_OutMin->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numYVect_OutMin->Location = System::Drawing::Point(479, 317);
			this->numYVect_OutMin->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numYVect_OutMin->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numYVect_OutMin->Name = L"numYVect_OutMin";
			this->numYVect_OutMin->Size = System::Drawing::Size(73, 22);
			this->numYVect_OutMin->TabIndex = 22;
			// 
			// numYVect_OutMax
			// 
			this->numYVect_OutMax->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numYVect_OutMax->Location = System::Drawing::Point(479, 343);
			this->numYVect_OutMax->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->numYVect_OutMax->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numYVect_OutMax->Name = L"numYVect_OutMax";
			this->numYVect_OutMax->Size = System::Drawing::Size(73, 22);
			this->numYVect_OutMax->TabIndex = 23;
			// 
			// pbxStatus
			// 
			this->pbxStatus->BackColor = System::Drawing::Color::Firebrick;
			this->pbxStatus->Location = System::Drawing::Point(-2, 506);
			this->pbxStatus->Name = L"pbxStatus";
			this->pbxStatus->Size = System::Drawing::Size(687, 37);
			this->pbxStatus->TabIndex = 79;
			this->pbxStatus->TabStop = false;
			// 
			// txtGeneral
			// 
			this->txtGeneral->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(63)), static_cast<System::Int32>(static_cast<System::Byte>(66)),
				static_cast<System::Int32>(static_cast<System::Byte>(65)));
			this->txtGeneral->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->txtGeneral->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->txtGeneral->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtGeneral->ForeColor = System::Drawing::SystemColors::Info;
			this->txtGeneral->Location = System::Drawing::Point(12, 15);
			this->txtGeneral->Multiline = true;
			this->txtGeneral->Name = L"txtGeneral";
			this->txtGeneral->ReadOnly = true;
			this->txtGeneral->Size = System::Drawing::Size(248, 19);
			this->txtGeneral->TabIndex = 81;
			this->txtGeneral->TabStop = false;
			this->txtGeneral->Text = L"General";
			this->txtGeneral->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// txtRC
			// 
			this->txtRC->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(63)), static_cast<System::Int32>(static_cast<System::Byte>(66)),
				static_cast<System::Int32>(static_cast<System::Byte>(65)));
			this->txtRC->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->txtRC->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->txtRC->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtRC->ForeColor = System::Drawing::SystemColors::Info;
			this->txtRC->Location = System::Drawing::Point(292, 54);
			this->txtRC->Multiline = true;
			this->txtRC->Name = L"txtRC";
			this->txtRC->ReadOnly = true;
			this->txtRC->Size = System::Drawing::Size(367, 19);
			this->txtRC->TabIndex = 82;
			this->txtRC->TabStop = false;
			this->txtRC->Text = L"RC";
			this->txtRC->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// txtVector
			// 
			this->txtVector->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(63)), static_cast<System::Int32>(static_cast<System::Byte>(66)),
				static_cast<System::Int32>(static_cast<System::Byte>(65)));
			this->txtVector->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->txtVector->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->txtVector->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtVector->ForeColor = System::Drawing::SystemColors::Info;
			this->txtVector->Location = System::Drawing::Point(292, 230);
			this->txtVector->Multiline = true;
			this->txtVector->Name = L"txtVector";
			this->txtVector->ReadOnly = true;
			this->txtVector->Size = System::Drawing::Size(367, 21);
			this->txtVector->TabIndex = 84;
			this->txtVector->TabStop = false;
			this->txtVector->Text = L"Vector";
			this->txtVector->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// pnlVector
			// 
			this->pnlVector->BackColor = System::Drawing::Color::White;
			this->pnlVector->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnlVector->Location = System::Drawing::Point(292, 249);
			this->pnlVector->Name = L"pnlVector";
			this->pnlVector->Size = System::Drawing::Size(367, 142);
			this->pnlVector->TabIndex = 99;
			this->pnlVector->MouseHover += gcnew System::EventHandler(this, &Main::pnlVector_MouseHover);
			// 
			// pnlRC
			// 
			this->pnlRC->BackColor = System::Drawing::Color::White;
			this->pnlRC->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnlRC->Location = System::Drawing::Point(292, 73);
			this->pnlRC->Name = L"pnlRC";
			this->pnlRC->Size = System::Drawing::Size(367, 142);
			this->pnlRC->TabIndex = 100;
			this->pnlRC->MouseHover += gcnew System::EventHandler(this, &Main::pnlRC_MouseHover);
			// 
			// pnlGeneral
			// 
			this->pnlGeneral->BackColor = System::Drawing::Color::White;
			this->pnlGeneral->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnlGeneral->Location = System::Drawing::Point(12, 34);
			this->pnlGeneral->Name = L"pnlGeneral";
			this->pnlGeneral->Size = System::Drawing::Size(248, 318);
			this->pnlGeneral->TabIndex = 0;
			this->pnlGeneral->MouseHover += gcnew System::EventHandler(this, &Main::pnlGeneral_MouseHover);
			// 
			// pnlBack
			// 
			this->pnlBack->BackColor = System::Drawing::Color::White;
			this->pnlBack->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnlBack->Controls->Add(this->txtGeneral);
			this->pnlBack->Controls->Add(this->chkIsDSLR);
			this->pnlBack->Controls->Add(this->lblCam_Btn_Delay);
			this->pnlBack->Controls->Add(this->lblCam_Trigger_Delay);
			this->pnlBack->Controls->Add(this->lblCam_Focus_Delay);
			this->pnlBack->Controls->Add(this->lblloop_Time);
			this->pnlBack->Controls->Add(this->numCam_Trigger_Delay);
			this->pnlBack->Controls->Add(this->numCam_Focus_Delay);
			this->pnlBack->Controls->Add(this->numLoop_Time);
			this->pnlBack->Controls->Add(this->numCam_Btn_Delay);
			this->pnlBack->Controls->Add(this->pnlGeneral);
			this->pnlBack->Location = System::Drawing::Point(14, 38);
			this->pnlBack->Name = L"pnlBack";
			this->pnlBack->Size = System::Drawing::Size(657, 421);
			this->pnlBack->TabIndex = 102;
			this->pnlBack->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::panel5_MouseMove);
			// 
			// lblV
			// 
			this->lblV->AutoSize = true;
			this->lblV->Location = System::Drawing::Point(628, 22);
			this->lblV->Name = L"lblV";
			this->lblV->Size = System::Drawing::Size(43, 13);
			this->lblV->TabIndex = 103;
			this->lblV->Text = L"v 1.377";
			this->lblV->MouseHover += gcnew System::EventHandler(this, &Main::lblV_MouseHover);
			// 
			// txtHelp
			// 
			this->txtHelp->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txtHelp->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->txtHelp->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtHelp->Location = System::Drawing::Point(2, 487);
			this->txtHelp->Name = L"txtHelp";
			this->txtHelp->ReadOnly = true;
			this->txtHelp->Size = System::Drawing::Size(683, 16);
			this->txtHelp->TabIndex = 104;
			this->txtHelp->TabStop = false;
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(232)), static_cast<System::Int32>(static_cast<System::Byte>(221)),
				static_cast<System::Int32>(static_cast<System::Byte>(209)));
			this->ClientSize = System::Drawing::Size(685, 541);
			this->Controls->Add(this->txtHelp);
			this->Controls->Add(this->lblV);
			this->Controls->Add(this->txtRC);
			this->Controls->Add(this->numYVect_OutMax);
			this->Controls->Add(this->numYVect_OutMin);
			this->Controls->Add(this->numYVect_InMax);
			this->Controls->Add(this->numYVect_InMin);
			this->Controls->Add(this->numXVect_OutMax);
			this->Controls->Add(this->numXVect_OutMin);
			this->Controls->Add(this->numXVect_InMax);
			this->Controls->Add(this->numXVect_InMin);
			this->Controls->Add(this->numYRcMapMax);
			this->Controls->Add(this->numYRcMapMin);
			this->Controls->Add(this->numYRcMax);
			this->Controls->Add(this->numYRcMin);
			this->Controls->Add(this->numXRcMapMax);
			this->Controls->Add(this->numXRcMapMin);
			this->Controls->Add(this->numXRcMax);
			this->Controls->Add(this->numXRcMin);
			this->Controls->Add(this->btnDefaults);
			this->Controls->Add(this->btnSaveToEEPROM);
			this->Controls->Add(this->btnSaveSettings);
			this->Controls->Add(this->lblYVect_OutMax);
			this->Controls->Add(this->lblYVect_OutMin);
			this->Controls->Add(this->lblYVect_InMax);
			this->Controls->Add(this->lblYVect_InMin);
			this->Controls->Add(this->lblXVect_OutMax);
			this->Controls->Add(this->lblXVect_OutMin);
			this->Controls->Add(this->lblXVectt_InMax);
			this->Controls->Add(this->lblXVect_InMin);
			this->Controls->Add(this->lblYRcMapMax);
			this->Controls->Add(this->lblYRcMapMin);
			this->Controls->Add(this->lblYRcMax);
			this->Controls->Add(this->lblYRcMin);
			this->Controls->Add(this->lblRcMapMax);
			this->Controls->Add(this->lblXRcMapMax);
			this->Controls->Add(this->lblXRcMax);
			this->Controls->Add(this->lblXRcMin);
			this->Controls->Add(this->btnGetSettings);
			this->Controls->Add(this->btnRefresh);
			this->Controls->Add(this->lblStatus);
			this->Controls->Add(this->btnOpen);
			this->Controls->Add(this->btnClose);
			this->Controls->Add(this->cboPorts);
			this->Controls->Add(this->pbxStatus);
			this->Controls->Add(this->txtVector);
			this->Controls->Add(this->pnlRC);
			this->Controls->Add(this->pnlVector);
			this->Controls->Add(this->pnlBack);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Main";
			this->Load += gcnew System::EventHandler(this, &Main::Main_Load);
			this->MouseHover += gcnew System::EventHandler(this, &Main::Main_MouseHover);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numCam_Trigger_Delay))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numCam_Focus_Delay))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numLoop_Time))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numCam_Btn_Delay))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numXRcMin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numXRcMax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numXRcMapMin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numXRcMapMax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numYRcMin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numYRcMax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numYRcMapMin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numYRcMapMax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numXVect_InMin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numXVect_InMax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numXVect_OutMin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numXVect_OutMax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numYVect_InMin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numYVect_InMax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numYVect_OutMin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numYVect_OutMax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbxStatus))->EndInit();
			this->pnlBack->ResumeLayout(false);
			this->pnlBack->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// find availeble ports
	
	delegate void SetTextBoxDtype(System::String ^);
	Form2^ hForm = nullptr;
	System::String^ helptxt;
	int helpNum = 0;

private: System::Void Main_Load(System::Object^  sender, System::EventArgs^  e) {
			 
			 this->btnClose->Enabled = false;
			 this->btnOpen->Enabled = true;
			 this->btnClose->Visible = false;
			 this->btnOpen->Visible = true;

			 this->btnGetSettings->Enabled = false;
			 this->btnSaveSettings->Enabled = false;
			 this->btnSaveToEEPROM->Enabled = false;
			
			 this->btnGetSettings->BackColor = Color::WhiteSmoke;
			 this->btnSaveSettings->BackColor = Color::WhiteSmoke;
			 this->btnSaveToEEPROM->BackColor = Color::WhiteSmoke;

			 this->cboPorts->Enabled = true;
			 this->btnRefresh->Enabled = true;

			 this->btnRefresh->BackColor = Color::DarkOrange;

			 this->lblStatus->Text = "Not Connected";
			 bool sendt = true;
			 this->cboPorts->Items->Clear();
			 this->cboPorts->Items->AddRange(m_serial->findPorts());
			 if (cboPorts->Items->Count >= 1)
			 {
				 cboPorts->SelectedIndex = 0;
			 }
			 if (cboPorts->Items->Count == 0)
			 {
				 cboPorts->Items->Add("No Ports");
				 cboPorts->SelectedItem = "No Ports";
			 }

			
			 
}
	
	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
				 
				 if (this->cboPorts->Text == String::Empty)
					 MessageBox::Show("No Port Selected", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);
				 else {
					 try{
						 // make sure port is not open
						 if ( m_serial->status() == 1){
							 //Set the name of the port from the combobox
							 if (this->cboPorts->Text->StartsWith("COM")){
								 m_serial->setName(this->cboPorts->Text);
								 //Open the serial port
								 m_serial->openPort();
								 pbxStatus->BackColor = Color::Green;
								 lblStatus->BackColor = Color::Green;
								 lblStatus->Text = String::Format("Connected to {0}", cboPorts->SelectedItem);
								 MessageBox::Show(String::Format("The connection to {0} has been established", cboPorts->SelectedItem), "Connection established", MessageBoxButtons::OK, MessageBoxIcon::Information, MessageBoxDefaultButton::Button1);
								 btnClose->Enabled = true;
								 btnOpen->Enabled = false;
								 btnClose->Visible = true;
								 btnOpen->Visible = false;

								 btnGetSettings->Enabled = true;
								 btnSaveSettings->Enabled = true;
								 btnSaveToEEPROM->Enabled = true;

								 btnGetSettings->BackColor = Color::DarkOrange;
								 btnSaveSettings->BackColor = Color::DarkOrange;
								 btnSaveToEEPROM->BackColor = Color::DarkOrange;

								 cboPorts->Enabled = false;
								 btnRefresh->Enabled = false;

								 btnRefresh->BackColor = Color::WhiteSmoke;
							 }
							 else
							 {
								 MessageBox::Show("No Port Selected", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error, MessageBoxDefaultButton::Button1);
							 }
						 }
						 else
							 MessageBox::Show("Port couldn't be openned", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error, MessageBoxDefaultButton::Button1);
					 }
					 catch (UnauthorizedAccessException^ ex){
						 MessageBox::Show(ex->Message, "Error occurred", MessageBoxButtons::OK, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);
					 }
				 }
			}
		 private: System::Void serialPort_DataRecived(System::Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e)
			 {
				 System::String^ indata = m_serial->readS();
				 SetTextBoxDtype ^pfnDelegate = gcnew SetTextBoxDtype(this, &Main::setText);
				 BeginInvoke(gcnew SetTextBoxDtype(this, &Main::setText), indata);
			 }
			 
				  
		  void setText(String ^indata){
					  
						  try {
							  if (indata->StartsWith("1") || indata->StartsWith("0"))
							  {
								  array<String^>^ data = indata->Split(',');
								  numCam_Trigger_Delay->Value = System::Int16::Parse(data[1]);
								  numCam_Trigger_Delay->Value = System::Int16::Parse(data[2]);
								  numCam_Focus_Delay->Value = System::Int16::Parse(data[3]);
								  numLoop_Time->Value = System::Int16::Parse(data[4]);
								  numXRcMin->Value = System::Int16::Parse(data[5]);
								  numXRcMax->Value = System::Int16::Parse(data[6]);
								  numXRcMapMin->Value = System::Int16::Parse(data[7]);
								  numXRcMapMax->Value = System::Int16::Parse(data[8]);
								  numYRcMin->Value = System::Int16::Parse(data[9]);
								  numYRcMax->Value = System::Int16::Parse(data[10]);
								  numYRcMapMin->Value = System::Int16::Parse(data[11]);
								  numYRcMapMax->Value = System::Int16::Parse(data[12]);
								  numXVect_InMin->Value = System::Int16::Parse(data[13]);
								  numXVect_InMax->Value = System::Int16::Parse(data[14]);
								  numXVect_OutMin->Value = System::Int16::Parse(data[15]);
								  numXVect_OutMax->Value = System::Int16::Parse(data[16]);
								  numYVect_InMin->Value = System::Int16::Parse(data[17]);
								  numYVect_InMax->Value = System::Int16::Parse(data[18]);
								  numYVect_OutMin->Value = System::Int16::Parse(data[19]);
								  numYVect_OutMax->Value = System::Int16::Parse(data[20]);

								  if (data[0] == "0")
								  {
									  chkIsDSLR->Checked = false;
								  }
								  if (data[0] == "1")
								  {
									  chkIsDSLR->Checked = true;
								  }
							  }
							  
							  
						  }
						  catch (Win32Exception^ ex)
						  {
							  Console::WriteLine(ex->Message);
						  }

					  
			}
			 
		private: System::Void btnClose_Click(System::Object^  sender, System::EventArgs^  e) {

					 try{
						 m_serial->closePort();
						 pbxStatus->BackColor = Color::Firebrick;
						 lblStatus->BackColor = Color::Firebrick;
						 lblStatus->Text = "Not Connected";
						 MessageBox::Show(String::Format("The connection to {0} has been terminated", cboPorts->SelectedItem), "Connection terminated", MessageBoxButtons::OK, MessageBoxIcon::Information, MessageBoxDefaultButton::Button1);
						 btnClose->Enabled = false;
						 btnOpen->Enabled = true;
						 btnClose->Visible = false;
						 btnOpen->Visible = true;
						

						 btnGetSettings->Enabled = false;
						 btnSaveSettings->Enabled = false;
						 btnSaveToEEPROM->Enabled = false;

						 btnGetSettings->BackColor = Color::WhiteSmoke;
						 btnSaveSettings->BackColor = Color::WhiteSmoke;
						 btnSaveToEEPROM->BackColor = Color::WhiteSmoke;

						 cboPorts->Enabled = true;
						 btnRefresh->Enabled = true;

						 btnRefresh->BackColor = Color::DarkOrange;
					 }
					 catch (UnauthorizedAccessException^ ex){
						 MessageBox::Show(ex->Message, "Error occurred", MessageBoxButtons::OK, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);
					 }
		}

private: System::Void btnRefresh_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->cboPorts->Items->Clear();
			 this->cboPorts->Items->AddRange(m_serial->findPorts());
			 if (cboPorts->Items->Count >= 1)
			 {
				 cboPorts->SelectedIndex = 0;
			 }
			 if (cboPorts->Items->Count == 0)
			 {
				 cboPorts->Items->Add("No Ports");
				 cboPorts->SelectedItem = "No Ports";
			 }
			 
}
private: System::Void btnSend_Click(System::Object^  sender, System::EventArgs^  e) {
			 m_serial->request();
			 m_serial->request();

			}			 
	private: System::Void btnSaveSettings_Click(System::Object^  sender, System::EventArgs^  e) {
				
					 __int16 cam_Btn_Delay = (int)numCam_Btn_Delay->Value;
					 __int16 cam_Trigger_Delay = (int)numCam_Trigger_Delay->Value;
					 __int16 cam_Focus_Delay = (int)numCam_Focus_Delay->Value;
					 __int16 loop_Time = (int)numLoop_Time->Value;
					 __int16 xRcMin = (int)numXRcMin->Value;
					 __int16 xRcMax = (int)numXRcMax->Value;
					 __int16 xRcMapMin = (int)numXRcMapMin->Value;
					 __int16 xRcMapMax = (int)numXRcMapMax->Value;
					 __int16 yRcMin = (int)numYRcMin->Value;
					 __int16 yRcMax = (int)numYRcMax->Value;
					 __int16 yRcMapMin = (int)numYRcMapMin->Value;
					 __int16 yRcMapMax = (int)numYRcMapMax->Value;
					 __int16 xVect_InMin = (int)numXVect_InMin->Value;
					 __int16 xVect_InMax = (int)numXVect_InMax->Value;
					 __int16 xVect_OutMin = (int)numXVect_OutMin->Value;
					 __int16 xVect_OutMax = (int)numXVect_OutMax->Value;
					 __int16 yVect_InMin = (int)numYVect_InMin->Value;
					 __int16 yVect_InMax = (int)numYVect_InMax->Value;
					 __int16 yVect_OutMin = (int)numYVect_OutMin->Value;
					 __int16 yVect_OutMax = (int)numYVect_OutMax->Value;
					 __int16 isDslr = 0;

					 if (chkIsDSLR->Checked == true)
					 {
						 isDslr = 1;
					 }
					


					 System::String^ settings = "setup" + isDslr.ToString() + "," + cam_Btn_Delay.ToString() + "," + cam_Trigger_Delay.ToString() + "," + cam_Focus_Delay.ToString() + "," + loop_Time.ToString() + "," + xRcMin.ToString() + "," + xRcMax.ToString() + "," + xRcMapMin.ToString() + "," + xRcMapMax.ToString() + "," + yRcMin.ToString() + "," + yRcMax.ToString() + "," + yRcMapMin.ToString() + "," + yRcMapMax.ToString() + "," + xVect_InMin.ToString() + "," + xVect_InMax.ToString() + "," + xVect_OutMin.ToString() + "," + xVect_OutMax.ToString() + "," + yVect_InMin.ToString() + "," + yVect_InMax.ToString() + "," + yVect_OutMin.ToString() + "," + yVect_OutMax.ToString() + ",";
					 m_serial->sendSettings(settings);

	}		
private: System::Void btnSaveToEEPROM_Click(System::Object^  sender, System::EventArgs^  e) {
			 m_serial->saveEEPROM();
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	
			 numCam_Btn_Delay->Value = 100;
			 numCam_Trigger_Delay->Value = 500;
			 numCam_Focus_Delay->Value = 200;
			 numLoop_Time->Value = 50;
			 numXRcMin->Value = 1916;
			 numXRcMax->Value = 1052;
			 numXRcMapMin->Value = -10;
			 numXRcMapMax->Value = 10;
			 numYRcMin->Value = 1040;
			 numYRcMax->Value = 1916;
			 numYRcMapMin->Value = -10;
			 numYRcMapMax->Value = 10;
			 numXVect_InMin->Value = -127;
			 numXVect_InMax->Value = 127;
			 numXVect_OutMin->Value = -38;
			 numXVect_OutMax->Value = 38;
			 numYVect_InMin->Value = -100;
			 numYVect_InMax->Value = 100;
			 numYVect_OutMin->Value = -38;
			 numYVect_OutMax->Value = 38;
			 chkIsDSLR->Checked = false;
}
#pragma region Help
		 void fillTxt(){
			 
				 switch (helpNum)
				 {
				 case 0:
					 helptxt = "";
					 break;
				 case 1:
					 helptxt = "DSLR is if the camera is using own trigger for autofocus";
					 break;
				 case 2:
					 helptxt = "Lengt of trigger button push(milliseconds)";
					 break;
				 case 3:
					 helptxt = "Minimum time(milliseconds) between pictures";
					 break;
				 case 4:
					 helptxt = "Focus time before triggering(milliseconds)";
					 break;
				 case 5:
					 helptxt = "Arduino minimum loop time";
					 break;
				 case 6:
					 helptxt = "Maximum PWM for X axis(microseconds)";
					 break;
				 case 7:
					 helptxt = "Minimum PWM for X axis(microseconds)";
					 break;
				 case 8:
					 helptxt = "Minimum RC throttle for X axix";
					 break;
				 case 9:
					 helptxt = "Maximum RC throttle for X axis";
					 break;
				 case 10:
					 helptxt = "Maximum PWM for Y axis(microseconds)";
					 break;
				 case 11:
					 helptxt = "Minimum PWM for Y axis(microseconds)";
					 break;
				 case 12:
					 helptxt = "Minimum RC throttle for Y axix";
					 break;
				 case 13:
					 helptxt = "Maximum RC throttle for Y axis";
					 break;
				 case 14:
					 helptxt = "Minimum X vector from Pixy";
					 break;
				 case 15:
					 helptxt = "Maximum X vector from Pixy";
					 break;
				 case 16:
					 helptxt = "Resolting degrees for minumum X vector from Pixy";
					 break;
				 case 17:
					 helptxt = "Resolting degrees for maximum X vector from Pixy";
					 break;
				 case 18:
					 helptxt = "Minimum Y vector from Pixy";
					 break;
				 case 19:
					 helptxt = "Maximum Y vector from Pixy";
					 break;
				 case 20:
					 helptxt = "Resolting degrees for minumum Y vector from Pixy";
					 break;
				 case 21:
					 helptxt = "Resolting degrees for maximum Y vector from Pixy";
					 break;
				 default:
					 helptxt = "Hover over a label to get more info about the parameter";
					 break;
				 }
				 txtHelp->Text = helptxt;
			 
		 }
private: System::Void chkIsDSLR_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 1;
			 fillTxt();
}
private: System::Void lblCam_Btn_Delay_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 2;
			 fillTxt();
}

private: System::Void lblCam_Trigger_Delay_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 3;
			 fillTxt();
}
private: System::Void lblCam_Focus_Delay_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 4;
			 fillTxt();
}
private: System::Void lblloop_Time_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 5;
			 fillTxt();
}
private: System::Void lblXRcMin_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 6;
			 fillTxt();
}
private: System::Void lblXRcMax_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 7;
			 fillTxt();
}
private: System::Void lblXRcMapMax_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 8;
			 fillTxt();
}
private: System::Void lblRcMapMax_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 9;
			 fillTxt();
}
private: System::Void lblYRcMin_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 10;
			 fillTxt();
}
private: System::Void lblYRcMax_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 11;
			 fillTxt();
}
private: System::Void lblYRcMapMin_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 12;
			 fillTxt();
}
private: System::Void lblYRcMapMax_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 13;
			 fillTxt();
}
private: System::Void lblXVect_InMin_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 14;
			 fillTxt();
}
private: System::Void lblXVectt_InMax_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 15;
			 fillTxt();
}
private: System::Void lblXVect_OutMin_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 16;
			 fillTxt();
}
private: System::Void lblXVect_OutMax_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 17;
			 fillTxt();
}
private: System::Void lblYVect_InMin_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 18;
			 fillTxt();
}
private: System::Void lblYVect_InMax_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 19;
			 fillTxt();
}
private: System::Void lblYVect_OutMin_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 20;
			 fillTxt();
}
private: System::Void lblYVect_OutMax_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 21;
			 fillTxt();
}

private: System::Void pnlGeneral_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 0;
			 fillTxt();
}
private: System::Void pnlRC_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 0;
			 fillTxt();
}

private: System::Void pnlVector_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 helpNum = 0;
			 fillTxt();
}
#pragma endregion Here is the code for helptext near bottom of gui


#pragma region Easter
private: System::Void lblV_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 if (hForm == nullptr)
			 {
				 hForm = gcnew Form2();
				 hForm->Show();
			 }
}

private: System::Void Main_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 if (hForm != nullptr)
			 {
				 hForm->Close();
				 hForm = nullptr;
			 }

}
private: System::Void panel5_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if (hForm != nullptr)
			 {
				 hForm->Close();
				 hForm = nullptr;
			 }
			 
}
#pragma endregion 



};

}