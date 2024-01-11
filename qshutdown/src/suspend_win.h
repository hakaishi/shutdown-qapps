#ifndef SUSPEND_WIN_H
#define SUSPEND_WIN_H

/*
 * external source code based on a blog post by Diomidis Spinellis
 *
 * correctly suspends Windows without going into hibernate
*/

/*
 * Copyright (c) 2008, Diomidis Spinellis
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include <stdio.h>

#include <windows.h>

/* Return as a string the error description for err */
static char *
wstrerror(LONG err)
{
    static LPVOID lpMsgBuf;

    if (lpMsgBuf)
        LocalFree(lpMsgBuf);
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, err,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPTSTR) &lpMsgBuf, 0, NULL);
    return (char*)lpMsgBuf;
}

int windowsSuspend()
{
    HANDLE tok;
    TOKEN_PRIVILEGES priv;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES |
                                                  TOKEN_QUERY, &tok) == 0) {
        fprintf(stderr, "OpenProcessToken: %s\n",
                wstrerror(GetLastError()));
        return (1);
    }

    // Get the LUID for shutdown privilege.
    if (LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
                             &priv.Privileges[0].Luid) == 0) {
        fprintf(stderr, "LookupPrivilegeValue: %s\n",
                wstrerror(GetLastError()));
        return (1);
    }

    // Enable AdjustTokenPrivileges.
    priv.PrivilegeCount = 1;
    priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (AdjustTokenPrivileges(tok, FALSE, &priv, 0, (PTOKEN_PRIVILEGES)NULL,
                              0) == 0 || GetLastError() != ERROR_SUCCESS) {
        fprintf(stderr, "AdjustTokenPrivileges: %s\n",
                wstrerror(GetLastError()));
        return (1);
    }

    // Force suspend
    if (SetSystemPowerState(TRUE, TRUE) == 0) {
        fprintf(stderr, "SetSystemPowerState: %s\n",
                wstrerror(GetLastError()));
        return (1);
    }
    return (0);
}

#endif // SUSPEND_WIN_H
