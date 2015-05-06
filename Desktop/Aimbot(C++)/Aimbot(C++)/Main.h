#pragma once
#define __DESKTOP
#include "Aimbot_Serial.h"


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
	private: System::Windows::Forms::TextBox^  txtRecived;
	private: System::Windows::Forms::ProgressBar^  pgbCS;



	private: System::Windows::Forms::Label^  lblPorts;
	private: System::Windows::Forms::Label^  lblStatus;
	private: System::Windows::Forms::Label^  lblRecived;
	private: System::Windows::Forms::Button^  btnRefresh;
	private: System::Windows::Forms::TextBox^  txt1;
	private: System::Windows::Forms::TextBox^  txt2;
	private: System::Windows::Forms::Button^  btnSend;
	private: System::Windows::Forms::TextBox^  txtCam_Btn_Delay;
	private: System::Windows::Forms::TextBox^  txtCam_Trigger_Delay;
	private: System::Windows::Forms::TextBox^  txtCam_Focus_Delay;
	private: System::Windows::Forms::TextBox^  txtLoop_Time;
	private: System::Windows::Forms::TextBox^  txtPWR_Check_Interval;
	private: System::Windows::Forms::TextBox^  txtXRcMin;

	private: System::Windows::Forms::TextBox^  txtXRcMax;
	private: System::Windows::Forms::TextBox^  txtXvect_InMin;








	private: System::Windows::Forms::TextBox^  txtYRcMapMax;


	private: System::Windows::Forms::TextBox^  txtYRcMapMin;
	private: System::Windows::Forms::TextBox^  txtYRcMax;


	private: System::Windows::Forms::TextBox^  txtYRcMin;




	private: System::Windows::Forms::TextBox^  txtXRcMapMax;
	private: System::Windows::Forms::TextBox^  txtXRcMapMin;
	private: System::Windows::Forms::TextBox^  txtYVect_OutMax;
	private: System::Windows::Forms::TextBox^  txtYVect_OutMin;







	private: System::Windows::Forms::TextBox^  txtYVect_InMax;

	private: System::Windows::Forms::TextBox^  txtYVect_InMin;

	private: System::Windows::Forms::TextBox^  txtXVect_OutMax;

	private: System::Windows::Forms::TextBox^  txtXVect_OutMin;


	private: System::Windows::Forms::TextBox^  txtXVect_InMax;
	private: System::Windows::Forms::CheckBox^  chkIsDSLR;


	private: System::Windows::Forms::Label^  lblCam_Btn_Delay;
	private: System::Windows::Forms::Label^  lblCam_Trigger_Delay;
	private: System::Windows::Forms::Label^  lblCam_Focus_Delay;
	private: System::Windows::Forms::Label^  lblloop_Time;
	private: System::Windows::Forms::Label^  lblPwr_Check_interval;
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
			this->serialPort = (gcnew System::IO::Ports::SerialPort(this->components));
			this->cboPorts = (gcnew System::Windows::Forms::ComboBox());
			this->btnClose = (gcnew System::Windows::Forms::Button());
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->txtRecived = (gcnew System::Windows::Forms::TextBox());
			this->pgbCS = (gcnew System::Windows::Forms::ProgressBar());
			this->lblPorts = (gcnew System::Windows::Forms::Label());
			this->lblStatus = (gcnew System::Windows::Forms::Label());
			this->lblRecived = (gcnew System::Windows::Forms::Label());
			this->btnRefresh = (gcnew System::Windows::Forms::Button());
			this->txt1 = (gcnew System::Windows::Forms::TextBox());
			this->txt2 = (gcnew System::Windows::Forms::TextBox());
			this->btnSend = (gcnew System::Windows::Forms::Button());
			this->txtCam_Btn_Delay = (gcnew System::Windows::Forms::TextBox());
			this->txtCam_Trigger_Delay = (gcnew System::Windows::Forms::TextBox());
			this->txtCam_Focus_Delay = (gcnew System::Windows::Forms::TextBox());
			this->txtLoop_Time = (gcnew System::Windows::Forms::TextBox());
			this->txtPWR_Check_Interval = (gcnew System::Windows::Forms::TextBox());
			this->txtXRcMin = (gcnew System::Windows::Forms::TextBox());
			this->txtXRcMax = (gcnew System::Windows::Forms::TextBox());
			this->txtXvect_InMin = (gcnew System::Windows::Forms::TextBox());
			this->txtYRcMapMax = (gcnew System::Windows::Forms::TextBox());
			this->txtYRcMapMin = (gcnew System::Windows::Forms::TextBox());
			this->txtYRcMax = (gcnew System::Windows::Forms::TextBox());
			this->txtYRcMin = (gcnew System::Windows::Forms::TextBox());
			this->txtXRcMapMax = (gcnew System::Windows::Forms::TextBox());
			this->txtXRcMapMin = (gcnew System::Windows::Forms::TextBox());
			this->txtYVect_OutMax = (gcnew System::Windows::Forms::TextBox());
			this->txtYVect_OutMin = (gcnew System::Windows::Forms::TextBox());
			this->txtYVect_InMax = (gcnew System::Windows::Forms::TextBox());
			this->txtYVect_InMin = (gcnew System::Windows::Forms::TextBox());
			this->txtXVect_OutMax = (gcnew System::Windows::Forms::TextBox());
			this->txtXVect_OutMin = (gcnew System::Windows::Forms::TextBox());
			this->txtXVect_InMax = (gcnew System::Windows::Forms::TextBox());
			this->chkIsDSLR = (gcnew System::Windows::Forms::CheckBox());
			this->lblCam_Btn_Delay = (gcnew System::Windows::Forms::Label());
			this->lblCam_Trigger_Delay = (gcnew System::Windows::Forms::Label());
			this->lblCam_Focus_Delay = (gcnew System::Windows::Forms::Label());
			this->lblloop_Time = (gcnew System::Windows::Forms::Label());
			this->lblPwr_Check_interval = (gcnew System::Windows::Forms::Label());
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
			this->SuspendLayout();
			// 
			// serialPort
			// 
			this->serialPort->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &Main::serialPort_DataRecived);
			// 
			// cboPorts
			// 
			this->cboPorts->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboPorts->FormattingEnabled = true;
			this->cboPorts->Location = System::Drawing::Point(12, 23);
			this->cboPorts->Name = L"cboPorts";
			this->cboPorts->Size = System::Drawing::Size(132, 21);
			this->cboPorts->TabIndex = 0;
			// 
			// btnClose
			// 
			this->btnClose->Location = System::Drawing::Point(81, 54);
			this->btnClose->Name = L"btnClose";
			this->btnClose->Size = System::Drawing::Size(63, 48);
			this->btnClose->TabIndex = 1;
			this->btnClose->Text = L"Close Port";
			this->btnClose->UseVisualStyleBackColor = true;
			this->btnClose->Click += gcnew System::EventHandler(this, &Main::btnClose_Click);
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(12, 54);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(63, 48);
			this->btnOpen->TabIndex = 2;
			this->btnOpen->Text = L"Open Port";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &Main::btnOpen_Click);
			// 
			// txtRecived
			// 
			this->txtRecived->Location = System::Drawing::Point(241, 23);
			this->txtRecived->Multiline = true;
			this->txtRecived->Name = L"txtRecived";
			this->txtRecived->ReadOnly = true;
			this->txtRecived->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txtRecived->Size = System::Drawing::Size(100, 130);
			this->txtRecived->TabIndex = 3;
			// 
			// pgbCS
			// 
			this->pgbCS->Location = System::Drawing::Point(0, 159);
			this->pgbCS->Name = L"pgbCS";
			this->pgbCS->Size = System::Drawing::Size(341, 23);
			this->pgbCS->TabIndex = 4;
			// 
			// lblPorts
			// 
			this->lblPorts->AutoSize = true;
			this->lblPorts->Location = System::Drawing::Point(12, 7);
			this->lblPorts->Name = L"lblPorts";
			this->lblPorts->Size = System::Drawing::Size(55, 13);
			this->lblPorts->TabIndex = 5;
			this->lblPorts->Text = L"Com Ports";
			// 
			// lblStatus
			// 
			this->lblStatus->AutoSize = true;
			this->lblStatus->Location = System::Drawing::Point(9, 143);
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(79, 13);
			this->lblStatus->TabIndex = 6;
			this->lblStatus->Text = L"Not Connected";
			// 
			// lblRecived
			// 
			this->lblRecived->AutoSize = true;
			this->lblRecived->Location = System::Drawing::Point(238, 7);
			this->lblRecived->Name = L"lblRecived";
			this->lblRecived->Size = System::Drawing::Size(73, 13);
			this->lblRecived->TabIndex = 7;
			this->lblRecived->Text = L"Data Recived";
			// 
			// btnRefresh
			// 
			this->btnRefresh->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->btnRefresh->Location = System::Drawing::Point(150, 24);
			this->btnRefresh->Name = L"btnRefresh";
			this->btnRefresh->Size = System::Drawing::Size(85, 20);
			this->btnRefresh->TabIndex = 8;
			this->btnRefresh->Text = L"Refresh";
			this->btnRefresh->UseVisualStyleBackColor = true;
			this->btnRefresh->Click += gcnew System::EventHandler(this, &Main::btnRefresh_Click);
			// 
			// txt1
			// 
			this->txt1->Location = System::Drawing::Point(150, 56);
			this->txt1->Name = L"txt1";
			this->txt1->Size = System::Drawing::Size(85, 20);
			this->txt1->TabIndex = 9;
			// 
			// txt2
			// 
			this->txt2->Location = System::Drawing::Point(150, 82);
			this->txt2->Name = L"txt2";
			this->txt2->Size = System::Drawing::Size(85, 20);
			this->txt2->TabIndex = 10;
			// 
			// btnSend
			// 
			this->btnSend->Location = System::Drawing::Point(12, 108);
			this->btnSend->Name = L"btnSend";
			this->btnSend->Size = System::Drawing::Size(132, 25);
			this->btnSend->TabIndex = 11;
			this->btnSend->Text = L"Send";
			this->btnSend->UseVisualStyleBackColor = true;
			this->btnSend->Click += gcnew System::EventHandler(this, &Main::btnSend_Click);
			// 
			// txtCam_Btn_Delay
			// 
			this->txtCam_Btn_Delay->Location = System::Drawing::Point(407, 123);
			this->txtCam_Btn_Delay->Name = L"txtCam_Btn_Delay";
			this->txtCam_Btn_Delay->Size = System::Drawing::Size(100, 20);
			this->txtCam_Btn_Delay->TabIndex = 12;
			// 
			// txtCam_Trigger_Delay
			// 
			this->txtCam_Trigger_Delay->Location = System::Drawing::Point(407, 198);
			this->txtCam_Trigger_Delay->Name = L"txtCam_Trigger_Delay";
			this->txtCam_Trigger_Delay->Size = System::Drawing::Size(100, 20);
			this->txtCam_Trigger_Delay->TabIndex = 13;
			// 
			// txtCam_Focus_Delay
			// 
			this->txtCam_Focus_Delay->Location = System::Drawing::Point(407, 224);
			this->txtCam_Focus_Delay->Name = L"txtCam_Focus_Delay";
			this->txtCam_Focus_Delay->Size = System::Drawing::Size(100, 20);
			this->txtCam_Focus_Delay->TabIndex = 14;
			// 
			// txtLoop_Time
			// 
			this->txtLoop_Time->Location = System::Drawing::Point(407, 250);
			this->txtLoop_Time->Name = L"txtLoop_Time";
			this->txtLoop_Time->Size = System::Drawing::Size(100, 20);
			this->txtLoop_Time->TabIndex = 15;
			// 
			// txtPWR_Check_Interval
			// 
			this->txtPWR_Check_Interval->Location = System::Drawing::Point(407, 276);
			this->txtPWR_Check_Interval->Name = L"txtPWR_Check_Interval";
			this->txtPWR_Check_Interval->Size = System::Drawing::Size(100, 20);
			this->txtPWR_Check_Interval->TabIndex = 16;
			// 
			// txtXRcMin
			// 
			this->txtXRcMin->Location = System::Drawing::Point(407, 299);
			this->txtXRcMin->Name = L"txtXRcMin";
			this->txtXRcMin->Size = System::Drawing::Size(100, 20);
			this->txtXRcMin->TabIndex = 17;
			// 
			// txtXRcMax
			// 
			this->txtXRcMax->Location = System::Drawing::Point(407, 325);
			this->txtXRcMax->Name = L"txtXRcMax";
			this->txtXRcMax->Size = System::Drawing::Size(100, 20);
			this->txtXRcMax->TabIndex = 18;
			// 
			// txtXvect_InMin
			// 
			this->txtXvect_InMin->Location = System::Drawing::Point(734, 350);
			this->txtXvect_InMin->Name = L"txtXvect_InMin";
			this->txtXvect_InMin->Size = System::Drawing::Size(100, 20);
			this->txtXvect_InMin->TabIndex = 25;
			// 
			// txtYRcMapMax
			// 
			this->txtYRcMapMax->Location = System::Drawing::Point(734, 324);
			this->txtYRcMapMax->Name = L"txtYRcMapMax";
			this->txtYRcMapMax->Size = System::Drawing::Size(100, 20);
			this->txtYRcMapMax->TabIndex = 24;
			// 
			// txtYRcMapMin
			// 
			this->txtYRcMapMin->Location = System::Drawing::Point(734, 301);
			this->txtYRcMapMin->Name = L"txtYRcMapMin";
			this->txtYRcMapMin->Size = System::Drawing::Size(100, 20);
			this->txtYRcMapMin->TabIndex = 23;
			// 
			// txtYRcMax
			// 
			this->txtYRcMax->Location = System::Drawing::Point(734, 275);
			this->txtYRcMax->Name = L"txtYRcMax";
			this->txtYRcMax->Size = System::Drawing::Size(100, 20);
			this->txtYRcMax->TabIndex = 22;
			// 
			// txtYRcMin
			// 
			this->txtYRcMin->Location = System::Drawing::Point(734, 249);
			this->txtYRcMin->Name = L"txtYRcMin";
			this->txtYRcMin->Size = System::Drawing::Size(100, 20);
			this->txtYRcMin->TabIndex = 21;
			// 
			// txtXRcMapMax
			// 
			this->txtXRcMapMax->Location = System::Drawing::Point(734, 223);
			this->txtXRcMapMax->Name = L"txtXRcMapMax";
			this->txtXRcMapMax->Size = System::Drawing::Size(100, 20);
			this->txtXRcMapMax->TabIndex = 20;
			// 
			// txtXRcMapMin
			// 
			this->txtXRcMapMin->Location = System::Drawing::Point(734, 197);
			this->txtXRcMapMin->Name = L"txtXRcMapMin";
			this->txtXRcMapMin->Size = System::Drawing::Size(100, 20);
			this->txtXRcMapMin->TabIndex = 19;
			// 
			// txtYVect_OutMax
			// 
			this->txtYVect_OutMax->Location = System::Drawing::Point(935, 347);
			this->txtYVect_OutMax->Name = L"txtYVect_OutMax";
			this->txtYVect_OutMax->Size = System::Drawing::Size(100, 20);
			this->txtYVect_OutMax->TabIndex = 32;
			// 
			// txtYVect_OutMin
			// 
			this->txtYVect_OutMin->Location = System::Drawing::Point(935, 321);
			this->txtYVect_OutMin->Name = L"txtYVect_OutMin";
			this->txtYVect_OutMin->Size = System::Drawing::Size(100, 20);
			this->txtYVect_OutMin->TabIndex = 31;
			// 
			// txtYVect_InMax
			// 
			this->txtYVect_InMax->Location = System::Drawing::Point(935, 298);
			this->txtYVect_InMax->Name = L"txtYVect_InMax";
			this->txtYVect_InMax->Size = System::Drawing::Size(100, 20);
			this->txtYVect_InMax->TabIndex = 30;
			// 
			// txtYVect_InMin
			// 
			this->txtYVect_InMin->Location = System::Drawing::Point(935, 272);
			this->txtYVect_InMin->Name = L"txtYVect_InMin";
			this->txtYVect_InMin->Size = System::Drawing::Size(100, 20);
			this->txtYVect_InMin->TabIndex = 29;
			// 
			// txtXVect_OutMax
			// 
			this->txtXVect_OutMax->Location = System::Drawing::Point(935, 246);
			this->txtXVect_OutMax->Name = L"txtXVect_OutMax";
			this->txtXVect_OutMax->Size = System::Drawing::Size(100, 20);
			this->txtXVect_OutMax->TabIndex = 28;
			// 
			// txtXVect_OutMin
			// 
			this->txtXVect_OutMin->Location = System::Drawing::Point(935, 220);
			this->txtXVect_OutMin->Name = L"txtXVect_OutMin";
			this->txtXVect_OutMin->Size = System::Drawing::Size(100, 20);
			this->txtXVect_OutMin->TabIndex = 27;
			// 
			// txtXVect_InMax
			// 
			this->txtXVect_InMax->Location = System::Drawing::Point(935, 194);
			this->txtXVect_InMax->Name = L"txtXVect_InMax";
			this->txtXVect_InMax->Size = System::Drawing::Size(100, 20);
			this->txtXVect_InMax->TabIndex = 26;
			// 
			// chkIsDSLR
			// 
			this->chkIsDSLR->AutoSize = true;
			this->chkIsDSLR->Location = System::Drawing::Point(407, 62);
			this->chkIsDSLR->Name = L"chkIsDSLR";
			this->chkIsDSLR->Size = System::Drawing::Size(55, 17);
			this->chkIsDSLR->TabIndex = 33;
			this->chkIsDSLR->Text = L"DSLR";
			this->chkIsDSLR->UseVisualStyleBackColor = true;
			// 
			// lblCam_Btn_Delay
			// 
			this->lblCam_Btn_Delay->AutoSize = true;
			this->lblCam_Btn_Delay->Location = System::Drawing::Point(513, 126);
			this->lblCam_Btn_Delay->Name = L"lblCam_Btn_Delay";
			this->lblCam_Btn_Delay->Size = System::Drawing::Size(107, 13);
			this->lblCam_Btn_Delay->TabIndex = 34;
			this->lblCam_Btn_Delay->Text = L"Camera Button Delay";
			// 
			// lblCam_Trigger_Delay
			// 
			this->lblCam_Trigger_Delay->AutoSize = true;
			this->lblCam_Trigger_Delay->Location = System::Drawing::Point(513, 201);
			this->lblCam_Trigger_Delay->Name = L"lblCam_Trigger_Delay";
			this->lblCam_Trigger_Delay->Size = System::Drawing::Size(103, 13);
			this->lblCam_Trigger_Delay->TabIndex = 35;
			this->lblCam_Trigger_Delay->Text = L"Camer Trigger Delay";
			// 
			// lblCam_Focus_Delay
			// 
			this->lblCam_Focus_Delay->AutoSize = true;
			this->lblCam_Focus_Delay->Location = System::Drawing::Point(513, 227);
			this->lblCam_Focus_Delay->Name = L"lblCam_Focus_Delay";
			this->lblCam_Focus_Delay->Size = System::Drawing::Size(105, 13);
			this->lblCam_Focus_Delay->TabIndex = 36;
			this->lblCam_Focus_Delay->Text = L"Camera Focus Delay";
			// 
			// lblloop_Time
			// 
			this->lblloop_Time->AutoSize = true;
			this->lblloop_Time->Location = System::Drawing::Point(513, 253);
			this->lblloop_Time->Name = L"lblloop_Time";
			this->lblloop_Time->Size = System::Drawing::Size(57, 13);
			this->lblloop_Time->TabIndex = 37;
			this->lblloop_Time->Text = L"Loop Time";
			// 
			// lblPwr_Check_interval
			// 
			this->lblPwr_Check_interval->AutoSize = true;
			this->lblPwr_Check_interval->Location = System::Drawing::Point(513, 279);
			this->lblPwr_Check_interval->Name = L"lblPwr_Check_interval";
			this->lblPwr_Check_interval->Size = System::Drawing::Size(109, 13);
			this->lblPwr_Check_interval->TabIndex = 38;
			this->lblPwr_Check_interval->Text = L"Power Check Interval";
			// 
			// lblXRcMin
			// 
			this->lblXRcMin->AutoSize = true;
			this->lblXRcMin->Location = System::Drawing::Point(513, 302);
			this->lblXRcMin->Name = L"lblXRcMin";
			this->lblXRcMin->Size = System::Drawing::Size(51, 13);
			this->lblXRcMin->TabIndex = 39;
			this->lblXRcMin->Text = L"X Rc Min";
			// 
			// lblXRcMax
			// 
			this->lblXRcMax->AutoSize = true;
			this->lblXRcMax->Location = System::Drawing::Point(513, 328);
			this->lblXRcMax->Name = L"lblXRcMax";
			this->lblXRcMax->Size = System::Drawing::Size(54, 13);
			this->lblXRcMax->TabIndex = 40;
			this->lblXRcMax->Text = L"X Rc Max";
			// 
			// lblXVect_InMin
			// 
			this->lblXVect_InMin->AutoSize = true;
			this->lblXVect_InMin->Location = System::Drawing::Point(840, 353);
			this->lblXVect_InMin->Name = L"lblXVect_InMin";
			this->lblXVect_InMin->Size = System::Drawing::Size(80, 13);
			this->lblXVect_InMin->TabIndex = 47;
			this->lblXVect_InMin->Text = L"X Vector In Min";
			// 
			// lblYRcMapMax
			// 
			this->lblYRcMapMax->AutoSize = true;
			this->lblYRcMapMax->Location = System::Drawing::Point(840, 327);
			this->lblYRcMapMax->Name = L"lblYRcMapMax";
			this->lblYRcMapMax->Size = System::Drawing::Size(78, 13);
			this->lblYRcMapMax->TabIndex = 46;
			this->lblYRcMapMax->Text = L"Y Rc Map Max";
			// 
			// lblYRcMapMin
			// 
			this->lblYRcMapMin->AutoSize = true;
			this->lblYRcMapMin->Location = System::Drawing::Point(840, 304);
			this->lblYRcMapMin->Name = L"lblYRcMapMin";
			this->lblYRcMapMin->Size = System::Drawing::Size(75, 13);
			this->lblYRcMapMin->TabIndex = 45;
			this->lblYRcMapMin->Text = L"Y Rc Map Min";
			// 
			// lblYRcMax
			// 
			this->lblYRcMax->AutoSize = true;
			this->lblYRcMax->Location = System::Drawing::Point(840, 278);
			this->lblYRcMax->Name = L"lblYRcMax";
			this->lblYRcMax->Size = System::Drawing::Size(54, 13);
			this->lblYRcMax->TabIndex = 44;
			this->lblYRcMax->Text = L"Y Rc Max";
			// 
			// lblYRcMin
			// 
			this->lblYRcMin->AutoSize = true;
			this->lblYRcMin->Location = System::Drawing::Point(840, 252);
			this->lblYRcMin->Name = L"lblYRcMin";
			this->lblYRcMin->Size = System::Drawing::Size(51, 13);
			this->lblYRcMin->TabIndex = 43;
			this->lblYRcMin->Text = L"Y Rc Min";
			// 
			// lblRcMapMax
			// 
			this->lblRcMapMax->AutoSize = true;
			this->lblRcMapMax->Location = System::Drawing::Point(840, 226);
			this->lblRcMapMax->Name = L"lblRcMapMax";
			this->lblRcMapMax->Size = System::Drawing::Size(78, 13);
			this->lblRcMapMax->TabIndex = 42;
			this->lblRcMapMax->Text = L"X Rc Map Max";
			// 
			// lblXRcMapMax
			// 
			this->lblXRcMapMax->AutoSize = true;
			this->lblXRcMapMax->Location = System::Drawing::Point(840, 200);
			this->lblXRcMapMax->Name = L"lblXRcMapMax";
			this->lblXRcMapMax->Size = System::Drawing::Size(75, 13);
			this->lblXRcMapMax->TabIndex = 41;
			this->lblXRcMapMax->Text = L"X Rc Map Min";
			// 
			// lblYVect_OutMax
			// 
			this->lblYVect_OutMax->AutoSize = true;
			this->lblYVect_OutMax->Location = System::Drawing::Point(1041, 350);
			this->lblYVect_OutMax->Name = L"lblYVect_OutMax";
			this->lblYVect_OutMax->Size = System::Drawing::Size(91, 13);
			this->lblYVect_OutMax->TabIndex = 54;
			this->lblYVect_OutMax->Text = L"Y Vector Out Max";
			// 
			// lblYVect_OutMin
			// 
			this->lblYVect_OutMin->AutoSize = true;
			this->lblYVect_OutMin->Location = System::Drawing::Point(1041, 324);
			this->lblYVect_OutMin->Name = L"lblYVect_OutMin";
			this->lblYVect_OutMin->Size = System::Drawing::Size(88, 13);
			this->lblYVect_OutMin->TabIndex = 53;
			this->lblYVect_OutMin->Text = L"Y Vector Out Min";
			// 
			// lblYVect_InMax
			// 
			this->lblYVect_InMax->AutoSize = true;
			this->lblYVect_InMax->Location = System::Drawing::Point(1041, 301);
			this->lblYVect_InMax->Name = L"lblYVect_InMax";
			this->lblYVect_InMax->Size = System::Drawing::Size(83, 13);
			this->lblYVect_InMax->TabIndex = 52;
			this->lblYVect_InMax->Text = L"Y Vector In Max";
			// 
			// lblYVect_InMin
			// 
			this->lblYVect_InMin->AutoSize = true;
			this->lblYVect_InMin->Location = System::Drawing::Point(1041, 275);
			this->lblYVect_InMin->Name = L"lblYVect_InMin";
			this->lblYVect_InMin->Size = System::Drawing::Size(80, 13);
			this->lblYVect_InMin->TabIndex = 51;
			this->lblYVect_InMin->Text = L"Y Vector In Min";
			// 
			// lblXVect_OutMax
			// 
			this->lblXVect_OutMax->AutoSize = true;
			this->lblXVect_OutMax->Location = System::Drawing::Point(1041, 249);
			this->lblXVect_OutMax->Name = L"lblXVect_OutMax";
			this->lblXVect_OutMax->Size = System::Drawing::Size(91, 13);
			this->lblXVect_OutMax->TabIndex = 50;
			this->lblXVect_OutMax->Text = L"X Vector Out Max";
			// 
			// lblXVect_OutMin
			// 
			this->lblXVect_OutMin->AutoSize = true;
			this->lblXVect_OutMin->Location = System::Drawing::Point(1041, 223);
			this->lblXVect_OutMin->Name = L"lblXVect_OutMin";
			this->lblXVect_OutMin->Size = System::Drawing::Size(88, 13);
			this->lblXVect_OutMin->TabIndex = 49;
			this->lblXVect_OutMin->Text = L"X Vector Out Min";
			// 
			// lblXVectt_InMax
			// 
			this->lblXVectt_InMax->AutoSize = true;
			this->lblXVectt_InMax->Location = System::Drawing::Point(1041, 197);
			this->lblXVectt_InMax->Name = L"lblXVectt_InMax";
			this->lblXVectt_InMax->Size = System::Drawing::Size(83, 13);
			this->lblXVectt_InMax->TabIndex = 48;
			this->lblXVectt_InMax->Text = L"X Vector In Max";
			// 
			// btnSaveSettings
			// 
			this->btnSaveSettings->Location = System::Drawing::Point(12, 220);
			this->btnSaveSettings->Name = L"btnSaveSettings";
			this->btnSaveSettings->Size = System::Drawing::Size(132, 20);
			this->btnSaveSettings->TabIndex = 55;
			this->btnSaveSettings->Text = L"Save Settings";
			this->btnSaveSettings->UseVisualStyleBackColor = true;
			this->btnSaveSettings->Click += gcnew System::EventHandler(this, &Main::btnSaveSettings_Click);
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1205, 498);
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
			this->Controls->Add(this->lblPwr_Check_interval);
			this->Controls->Add(this->lblloop_Time);
			this->Controls->Add(this->lblCam_Focus_Delay);
			this->Controls->Add(this->lblCam_Trigger_Delay);
			this->Controls->Add(this->lblCam_Btn_Delay);
			this->Controls->Add(this->chkIsDSLR);
			this->Controls->Add(this->txtYVect_OutMax);
			this->Controls->Add(this->txtYVect_OutMin);
			this->Controls->Add(this->txtYVect_InMax);
			this->Controls->Add(this->txtYVect_InMin);
			this->Controls->Add(this->txtXVect_OutMax);
			this->Controls->Add(this->txtXVect_OutMin);
			this->Controls->Add(this->txtXVect_InMax);
			this->Controls->Add(this->txtXvect_InMin);
			this->Controls->Add(this->txtYRcMapMax);
			this->Controls->Add(this->txtYRcMapMin);
			this->Controls->Add(this->txtYRcMax);
			this->Controls->Add(this->txtYRcMin);
			this->Controls->Add(this->txtXRcMapMax);
			this->Controls->Add(this->txtXRcMapMin);
			this->Controls->Add(this->txtXRcMax);
			this->Controls->Add(this->txtXRcMin);
			this->Controls->Add(this->txtPWR_Check_Interval);
			this->Controls->Add(this->txtLoop_Time);
			this->Controls->Add(this->txtCam_Focus_Delay);
			this->Controls->Add(this->txtCam_Trigger_Delay);
			this->Controls->Add(this->txtCam_Btn_Delay);
			this->Controls->Add(this->btnSend);
			this->Controls->Add(this->txt2);
			this->Controls->Add(this->txt1);
			this->Controls->Add(this->btnRefresh);
			this->Controls->Add(this->lblRecived);
			this->Controls->Add(this->lblStatus);
			this->Controls->Add(this->lblPorts);
			this->Controls->Add(this->pgbCS);
			this->Controls->Add(this->txtRecived);
			this->Controls->Add(this->btnOpen);
			this->Controls->Add(this->btnClose);
			this->Controls->Add(this->cboPorts);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"Main";
			this->Text = L"47";
			this->Load += gcnew System::EventHandler(this, &Main::Main_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// find availeble ports
	
	delegate void SetTextBoxDtype(System::String ^);
	

private: System::Void Main_Load(System::Object^  sender, System::EventArgs^  e) {
			 this->cboPorts->Items->AddRange(m_serial->findPorts());
			 this->btnClose->Enabled = false;
			 this->btnOpen->Enabled = true;
			 this->btnSend->Enabled = false;
			 this->cboPorts->Enabled = true;
			 this->btnRefresh->Enabled = true;
			 this->lblStatus->Text = "Not Connected";
			 bool sendt = true;
}
	
	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->txtRecived->Clear();
				 if (this->cboPorts->Text == String::Empty)
					 MessageBox::Show("No Port Selected", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);
				 else {
					 try{
						 // make sure port is not open
						 if ( m_serial->status() == 1){
							 //Set the name of the port from the combobox
							 m_serial->setName(this->cboPorts->Text);
							 //Open the serial port
							 m_serial->openPort();
							 this->pgbCS->Value = 100;
							 lblStatus->Text = String::Format("Connected to {0}", cboPorts->SelectedItem);
							 MessageBox::Show(String::Format("The connection to {0} has been established", cboPorts->SelectedItem), "Connection established", MessageBoxButtons::OK, MessageBoxIcon::Information, MessageBoxDefaultButton::Button1);
							 btnClose->Enabled = true;
							 btnOpen->Enabled = false;
							 btnSend->Enabled = true;
							 cboPorts->Enabled = false;
							 btnRefresh->Enabled = false;
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
				 txtRecived->BeginInvoke(gcnew SetTextBoxDtype(this, &Main::setText), indata);
			 }
			 
				  
		  void setText(String ^indata){
					  
						  try {
							
								  array<String^>^ data = indata->Split(',');
								  txtCam_Btn_Delay->Text = data[1];
								  txtCam_Trigger_Delay->Text = data[2];
								  txtCam_Focus_Delay->Text = data[3];
								  txtLoop_Time->Text = data[4];
								  txtPWR_Check_Interval->Text = data[5];
								  txtXRcMin->Text = data[6];
								  txtXRcMax->Text = data[7];
								  txtXRcMapMin->Text = data[8];
								  txtXRcMapMax->Text = data[9];
								  txtYRcMin->Text = data[10];
								  txtYRcMax->Text = data[11];
								  txtYRcMapMin->Text = data[12];
								  txtYRcMapMax->Text = data[13];
								  txtXvect_InMin->Text = data[14];
								  txtXVect_InMax->Text = data[15];
								  txtXVect_OutMin->Text = data[16];
								  txtXVect_OutMax->Text = data[17];
								  txtYVect_InMin->Text = data[18];
								  txtYVect_InMax->Text = data[19];
								  txtYVect_OutMin->Text = data[20];
								  txtYVect_OutMax->Text = data[21];

								  if (data[0] == "0")
								  {
									  chkIsDSLR->Checked = false;
								  }
								  if (data[0] == "1")
								  {
									  chkIsDSLR->Checked = true;
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
						 pgbCS->Value = 0;
						 lblStatus->Text = "Not Connected";
						 MessageBox::Show(String::Format("The connection to {0} has been terminated", cboPorts->SelectedItem), "Connection terminated", MessageBoxButtons::OK, MessageBoxIcon::Information, MessageBoxDefaultButton::Button1);
						 btnClose->Enabled = false;
						 btnOpen->Enabled = true;
						 btnSend->Enabled = false;
						 cboPorts->Enabled = true;
						 btnRefresh->Enabled = true;
					 }
					 catch (UnauthorizedAccessException^ ex){
						 MessageBox::Show(ex->Message, "Error occurred", MessageBoxButtons::OK, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);
					 }
		}

private: System::Void btnRefresh_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->cboPorts->Items->Clear();
			 this->cboPorts->Items->AddRange(m_serial->findPorts());
}
private: System::Void btnSend_Click(System::Object^  sender, System::EventArgs^  e) {
			 m_serial->request();

			 
			}			 
	private: System::Void btnSaveSettings_Click(System::Object^  sender, System::EventArgs^  e) {
				
					 __int16 cam_Btn_Delay = System::Int16::Parse(txtCam_Btn_Delay->Text);
					 __int16 cam_Trigger_Delay= System::Int16::Parse(txtCam_Trigger_Delay->Text);
					 __int16 cam_Focus_Delay = System::Int16::Parse(txtCam_Focus_Delay->Text);
					 __int16 loop_Time = System::Int16::Parse(txtLoop_Time->Text);
					 __int16 pwr_Check_Interval = System::Int16::Parse(txtPWR_Check_Interval->Text);
					 __int16 xRcMin = System::Int16::Parse(txtXRcMin->Text);
					 __int16 xRcMax= System::Int16::Parse(txtXRcMax->Text);
					 __int16 xRcMapMin = System::Int16::Parse(txtXRcMapMin->Text);
					 __int16 xRcMapMax = System::Int16::Parse(txtXRcMapMax->Text);
					 __int16 yRcMin = System::Int16::Parse(txtYRcMin->Text);
					 __int16 yRcMax = System::Int16::Parse(txtYRcMax->Text);
					 __int16 yRcMapMin = System::Int16::Parse(txtYRcMapMin->Text);
					 __int16 yRcMapMax = System::Int16::Parse(txtYRcMapMax->Text);
					 __int16 xVect_InMin = System::Int16::Parse(txtXvect_InMin->Text);
					 __int16 xVect_InMax = System::Int16::Parse(txtXVect_InMax->Text);
					 __int16 xVect_OutMin = System::Int16::Parse(txtXVect_OutMin->Text);
					 __int16 xVect_OutMax = System::Int16::Parse(txtXVect_OutMax->Text);
					 __int16 yVect_InMin = System::Int16::Parse(txtYVect_InMin->Text);
					 __int16 yVect_InMax = System::Int16::Parse(txtYVect_InMax->Text);
					 __int16 yVect_OutMin = System::Int16::Parse(txtXVect_OutMin->Text);
					 __int16 yVect_OutMax = System::Int16::Parse(txtYVect_OutMax->Text);
					 __int16 isDslr;

					 if (chkIsDSLR->Checked == true)
					 {
						 isDslr = 1;
					 }
					 if (chkIsDSLR->Checked == false)
					 {
						 isDslr = 0;
					 }


					 System::String^ settings = "setup" + isDslr.ToString() + "," + cam_Btn_Delay.ToString() + "," + cam_Trigger_Delay.ToString() + "," + cam_Focus_Delay.ToString() + "," + loop_Time.ToString() + "," + pwr_Check_Interval.ToString() + "," + xRcMin.ToString() + "," + xRcMax.ToString() + "," + xRcMapMin.ToString() + "," + xRcMapMax.ToString() + "," + yRcMin.ToString() + "," + yRcMax.ToString() + "," + yRcMapMin.ToString() + "," + yRcMapMax.ToString() + "," + xVect_InMin.ToString() + "," + xVect_InMax.ToString() + "," + xVect_OutMin.ToString() + "," + xVect_OutMax.ToString() + "," + yVect_InMin.ToString() + "," + yVect_InMax.ToString() + "," + yVect_OutMin.ToString() + "," + yVect_OutMax.ToString() + ",";
					 m_serial->sendSettings(settings);

					 
				
	}		
};
}