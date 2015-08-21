
void ShowAboutBox(CString sTitle, UINT nIconID)
{
	CString sDeveloper;
	sDeveloper = "Developer : Barretto VN \nE-Mail : barretto_vn@mail.com";

	if(nIconID == NULL)
		ShellAbout(NULL, sTitle, sDeveloper, NULL);
	else
	{
		CWinApp* pApp= AfxGetApp();
		ShellAbout(NULL, sTitle , sDeveloper , pApp->LoadIcon(nIconID));
	}
	return;
}