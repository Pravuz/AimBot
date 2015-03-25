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
			this->pgbCS->Size = System::Drawing::Size(350, 23);
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
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(344, 188);
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
			this->Text = L"Main";
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

							txtRecived->AppendText(indata);
							txtRecived->AppendText("\n");
							txtRecived->ScrollToCaret();
							if (indata->StartsWith("txt1")){
								array<String^>^ data = indata->Split(':');
								txt1->Text = data[1];
							}
							if (indata->StartsWith("txt2")){
								array<String^>^ data = indata->Split(':');
								txt2->Text = data[1];
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
};
}