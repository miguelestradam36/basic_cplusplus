// POPO.cpp : Defines the entry point for the application.
//

/*
Miguel Estrada Murillo;
Grupo 5;
Analisis y Diseño de Algoritmos;
Proyecto de Conversion de Temperaturas;

Yo ya habia llevado un poco de programación en C++ antes

*/


#include "framework.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_POPO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_POPO));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POPO));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_POPO);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, L"Proyecto de Temperaturas", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

wchar_t valor_numerico[30];
wchar_t unidad_inicial[30];
wchar_t unidad_final[30];
HWND* NUMERO;
HWND* UNIDAD_PRI;
HWND* UNIDAD_SEG;
HWND* RESULTADO_FINAL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                //Miguel Estrada - Descriptive and drawing code goes here
                //Beginnig

                TCHAR usuario[] = _T("Miguel Estrada Murillo   |   Carné = 2020026644");
                TextOut(hdc, 10, 10, usuario, _tcslen(usuario));

                TCHAR titulo[] = _T("Proyecto Conversión Temperaturas");
                TextOut(hdc, 10, 40, titulo, _tcslen(titulo));

                TCHAR convertir[] = _T("Introduzca un valor y seleccione las unidades: ");
                TextOut(hdc, 10, 120, convertir, _tcslen(convertir));

                TCHAR convertido[] = _T("Resultado de la conversión: ");
                TextOut(hdc, 500, 120, convertido, _tcslen(convertido));

                TCHAR From[] = _T("De ");
                TextOut(hdc, 10, 190, From, _tcsclen(From));

                TCHAR To[] = _T(" a ");
                TextOut(hdc, 160, 190, To, _tcsclen(To));

                //My description code ends here
                //Finito

                EndPaint(hWnd, &ps);
            }
            break;
        case WM_CREATE:
        {
            //All this code was made by Miguel Estrada
            //BEGIN
            static HWND hwdValorNumerico = CreateWindow(
                L"Edit",
                L"Introduzca solamente números",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                10,
                150,
                260,
                25,
                hWnd,
                NULL,
                NULL,
                NUMERO
            );

            static HWND hwndButton = CreateWindow(
                L"BUTTON",
                L"Convertir",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                280,
                150,
                80,
                25,
                hWnd,
                (HMENU)1,
                NULL,
                NULL);

            static HWND hwdInicial = CreateWindow(
                WC_COMBOBOX,
                TEXT(""),
                CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
                40,
                190,
                100,
                75,
                hWnd,
                NULL,
                NULL,
                UNIDAD_PRI
            );

            SendMessage(hwdInicial, CB_ADDSTRING, 0, (LPARAM)TEXT("Celsius"));
            SendMessage(hwdInicial, CB_ADDSTRING, 1, (LPARAM)TEXT("Kelvin"));
            SendMessage(hwdInicial, CB_ADDSTRING, 2, (LPARAM)TEXT("Fahrenheit"));

            SendMessage(hwdInicial, CB_SETCURSEL, (WPARAM)1, (LPARAM)0);

            static HWND hwdFinal = CreateWindow(
                WC_COMBOBOX,
                TEXT(""),
                CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
                200,
                190,
                100,
                75,
                hWnd,
                NULL,
                NULL,
                UNIDAD_SEG
            );

            SendMessage(hwdFinal, CB_ADDSTRING, 0, (LPARAM)TEXT("Celsius"));
            SendMessage(hwdFinal, CB_ADDSTRING, 1, (LPARAM)TEXT("Kelvin"));
            SendMessage(hwdFinal, CB_ADDSTRING, 2, (LPARAM)TEXT("Fahrenheit"));

            SendMessage(hwdFinal, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);

            HWND hwdResultado = CreateWindow(
                L"Edit",
                L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                500,
                150,
                360,
                25,
                hWnd,
                NULL,
                NULL,
                RESULTADO_FINAL
            );

            UNIDAD_PRI = &hwdInicial;
            UNIDAD_SEG = &hwdFinal;
            NUMERO = &hwdValorNumerico;
            RESULTADO_FINAL = &hwdResultado;
        
            //GetWindowText(hwdValorNumerico, valor_numerico, 30);
            //::MessageBox(hWnd, valor_numerico, L"Title", NULL);

            //GetWindowText(hwdInicial, unidad_inicial, 30);
            //::MessageBox(hWnd, unidad_inicial, L"Title", NULL);

            //GetWindowText(hwdFinal, unidad_final, 30);
            //::MessageBox(hWnd, unidad_final, L"Title", NULL);

        }
        case WM_COMMAND:
            {
                int wmId = LOWORD(wParam);
                switch (wmId)
                {
                    case 1:
                        if ((HIWORD(wParam) == BN_CLICKED) && (lParam != 0))
                        {   
                            int unidad_primera = GetWindowText(*UNIDAD_PRI, unidad_inicial, 30);
                            int unidad_segunda = GetWindowText(*UNIDAD_SEG, unidad_final, 30);
                            int valor_numeral = GetWindowText(*NUMERO, valor_numerico, 30);

                            std::string Celsius = "Celsius";
                            std::string Kelvin = "Kelvin";
                            std::string Fahrenheit = "Fahrenheit";

                            std::string Unidad_Inicial_usada;
                            std::string Unidad_Final_usada;
                            std::string Valor_Numerico_usado;

                            #ifdef UNICODE

                            std::wstring inicial = unidad_inicial;
                            std::wstring final = unidad_final;
                            std::wstring numero = valor_numerico;

                            Unidad_Inicial_usada = std::string(inicial.begin(), inicial.end());
                            Unidad_Final_usada = std::string(final.begin(), final.end());
                            Valor_Numerico_usado = std::string(numero.begin(), numero.end());

                            #else

                            Unidad_Inicial_usada = unidad_inicial;
                            Unidad_Final_usada = unidad_final;

                            #endif

                            double resultado_final;
                            double numero_para_calculo;
                            try
                            {
                                numero_para_calculo = std::stoi(Valor_Numerico_usado);
                            }
                            catch(...)
                            {
                                ::MessageBox(hWnd, L"Introduzca un numero", L"Valor no aceptado", NULL);
                                break;
                                return 1;
                            }
                            if (unidad_primera == unidad_segunda)
                            {
                                HWND hwdResultado_igual = CreateWindow(
                                    L"Edit",
                                    L"Unidad inicial y final para la conversión son iguales",
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    500,
                                    150,
                                    360,
                                    25,
                                    hWnd,
                                    NULL,
                                    NULL,
                                    RESULTADO_FINAL
                                );
                                break;
                                return 1;
                            }
                            else if (unidad_primera != unidad_segunda)
                            {
                                if (numero_para_calculo == NULL)
                                {
                                    ::MessageBox(hWnd, L"Por favor ingrese un valor numerico", L"Valor no aceptado", NULL);
                                    break;
                                    return 1;
                                }
                                if (Unidad_Inicial_usada == Celsius)
                                {
                                    if (Unidad_Final_usada == Fahrenheit)
                                    {
                                        resultado_final = (numero_para_calculo * 1.8) + 32;
                                    }
                                    else if (Unidad_Final_usada == Kelvin)
                                    {
                                        resultado_final = numero_para_calculo + 273.15;
                                    }
                                    else 
                                    {
                                        ::MessageBox(hWnd, L"La Unidad Final no puede ser distinta a sus opciones", L"Valor no aceptado", NULL);
                                        break;
                                    }

                                }
                                else if (Unidad_Inicial_usada == Kelvin)
                                {
                                    if (Unidad_Final_usada == Fahrenheit) 
                                    {
                                        resultado_final = ((numero_para_calculo - 273.15) * 1.8) + 32;
                                    }
                                    else if (Unidad_Final_usada == Celsius) 
                                    {
                                        resultado_final = numero_para_calculo - 273.15;
                                    }
                                    else 
                                    {
                                        ::MessageBox(hWnd, L"La Unidad Final no puede ser distinta a sus opciones", L"Valor no aceptado", NULL);
                                        break;
                                    }
                                }
                                else if (Unidad_Inicial_usada == Fahrenheit)
                                {
                                    if (Unidad_Final_usada == Celsius) 
                                    {
                                        resultado_final = (numero_para_calculo - 32) * 1.8;
                                    }
                                    else if (Unidad_Final_usada == Kelvin) 
                                    {
                                        resultado_final = ((numero_para_calculo - 32) * 1.8) + 273.15;
                                    }
                                    else 
                                    {
                                        ::MessageBox(hWnd, L"La Unidad Final no puede ser distinta a sus opciones", L"Valor no aceptado", NULL);
                                        break;
                                    }
                                }
                                else 
                                {
                                    ::MessageBox(hWnd, L"Una de sus acciones generó la perdida de datos esenciales para la ejecución del programa", L"Perdida de Información", NULL);
                                    break;
                                }
                            }
                            else 
                            {
                                ::MessageBox(hWnd, L"Por favor no elimine la informacion disponible, limitese a seguir las instrucciones", L"Accion generó un error", NULL);
                                break;
                            }
                            //Now let's display the information provided
                            //Mas dificil de lo que pense hacerlo en visual studio jeje

                            std::string resultado_str = std::to_string(resultado_final);
                            std::wstring Display(resultado_str.begin(), resultado_str.end());
                            LPCWSTR Display_off = Display.c_str();


                            HWND hwdResultado_igual = CreateWindow(
                                L"Edit",
                                Display_off,
                                WS_CHILD | WS_VISIBLE | WS_BORDER,
                                500,
                                150,
                                360,
                                25,
                                hWnd,
                                NULL,
                                NULL,
                                RESULTADO_FINAL
                            );

                            //end
                        }
                        break;
                    case IDM_ABOUT:
                        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                        break;
                    case IDM_EXIT:
                        DestroyWindow(hWnd);
                        break;
                    default:
                        return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
