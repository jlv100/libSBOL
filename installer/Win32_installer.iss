; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "libSBOL"
#define MyAppVersion "2.3.0"
#define MyAppSubVersion ""
#define MyPlatform "Win"
#define MyArchitecture "x86"
#define MyAppPublisher "SBOL Team"
#define MyAppURL "http://sbolstandard.org/"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{D4595067-D8B3-457C-89C5-1A98C7A5338F}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\SBOL
OutputBaseFilename={#MyAppName}-{#MyAppVersion}{#MyAppSubVersion}-{#MyPlatform}-{#MyArchitecture}
OutputDir = ..\dist
DirExistsWarning=no
DisableWelcomePage=no
DisableProgramGroupPage=yes
Compression=lzma2/fast
SolidCompression=no
PrivilegesRequired=admin
RestartApplications=no

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

; Specify the file paths!
[Files]
Source: "..\install_2_{#MyArchitecture}\lib\*"; DestDir: "{app}\lib"; Flags: ignoreversion
Source: "..\install_2_{#MyArchitecture}\include\*"; DestDir: "{app}\include"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

