#include <windows.h>
#include <ctime>
#include <cstdlib>

HWND hEdit, hButton, hLabelTitle, hLabelResult;
int randomNumber;
HFONT hFont;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {
        case WM_CREATE:
        {
            srand(time(0));
            randomNumber = rand() % 100 + 1;

            hFont = CreateFont(22, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                               ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                               CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                               DEFAULT_PITCH | FF_SWISS, "Arial");

            // Title (never changes)
            hLabelTitle = CreateWindow("STATIC",
                "Guess a number between 1 and 100",
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                50, 30, 400, 40,
                hwnd, NULL, NULL, NULL);

            // Input box
            hEdit = CreateWindow("EDIT", "",
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER,
                150, 90, 200, 40,
                hwnd, NULL, NULL, NULL);

            // Button
            hButton = CreateWindow("BUTTON", "Check Guess",
                WS_VISIBLE | WS_CHILD,
                150, 150, 200, 45,
                hwnd, (HMENU)1, NULL, NULL);

            // Result label (separate)
            hLabelResult = CreateWindow("STATIC", "",
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                50, 210, 400, 40,
                hwnd, NULL, NULL, NULL);

            SendMessage(hLabelTitle, WM_SETFONT, (WPARAM)hFont, TRUE);
            SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
            SendMessage(hButton, WM_SETFONT, (WPARAM)hFont, TRUE);
            SendMessage(hLabelResult, WM_SETFONT, (WPARAM)hFont, TRUE);
        }
        break;

        case WM_COMMAND:
        {
            if(LOWORD(wp) == 1)
            {
                char input[10];
                GetWindowText(hEdit, input, 10);
                int guess = atoi(input);

                if(guess < randomNumber)
                    SetWindowText(hLabelResult, "Too Low! Try Again.");
                else if(guess > randomNumber)
                    SetWindowText(hLabelResult, "Too High! Try Again.");
                else
                {
                    SetWindowText(hLabelResult, "Correct Guess!");
                    MessageBox(hwnd, "Congratulations! You Won!",
                               "Winner", MB_OK | MB_ICONINFORMATION);
                }
            }
        }
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
    WNDCLASS wc = {0};
    wc.lpszClassName = "GuessGame";
    wc.hInstance = hInst;
    wc.lpfnWndProc = WindowProcedure;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    RegisterClass(&wc);

    CreateWindow("GuessGame", "Guess The Number Game",
                 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                 300, 100, 520, 350,
                 NULL, NULL, hInst, NULL);

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}