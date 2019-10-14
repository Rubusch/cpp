/*
 * Copyright (c) 2007, IRTrans GmbH
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of IRTrans GmbH nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY IRTrans GmbH ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL IRTrans GmbH BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#define ERR_OPEN 1
#define ERR_RESET 2
#define ERR_VERSION 3
#define ERR_TIMEOUT 4
#define ERR_READVERSION 5
#define ERR_USBCOM 6
#define ERR_NETIO 7

#define ERR_DBOPENINPUT 11
#define ERR_REMOTENOTFOUND 12
#define ERR_COMMANDNOTFOUND 13
#define ERR_TIMINGNOTFOUND 14
#define ERR_OPENASCII 15
#define ERR_NODATABASE 16
#define ERR_OPENUSB 17
#define ERR_RESEND 18
#define ERR_TOGGLE_DUP 19
#define ERR_DBOPENINCLUDE 20
#define ERR_NOFILEOPEN 21
#define ERR_FLOCK 22
#define ERR_STTY 23
#define ERR_HOTCODE 24
#define ERR_NOTIMING 25
#define ERR_TEMPCOMMAND 26
#define ERR_OPENTRANS 27
#define ERR_TESTCOM 28
#define ERR_SHUTDOWN 29
#define ERR_ISMACRO 30
#define ERR_LONGRAW 31
#define ERR_LONGDATA 32
#define ERR_WRONGBUS 33
#define ERR_COMMANDSTRING 34
#define ERR_OVERWRITE 35
#define ERR_CCF 36
#define ERR_UDPFORMAT 37
#define ERR_TESTCOMOK 38
#define ERR_NOIRDB 39
#define ERR_NOTSUPPORTED 40
#define ERR_NO_RS232 41
#define ERR_SENDOK 42
#define ERR_CCFLEN 43
#define ERR_ACTIONSEND 44
#define ERR_CCFSYNTAX 45
#define ERR_SSID_WLAN 46
#define ERR_SEND_DISABLED 47
#define ERR_SEND_LED 48
#define ERR_IRDB_EMPTY 49
#define ERR_OUTPUT_BUSY 50
#define ERR_MACRO_LENGTH 51
#define ERR_MACRO_COUNT 52
#define ERR_NO_MACRO 53
#define ERR_ANALOG 54


#define ERR_LEARN_LENGTH 95
#define ERR_LEARN_RAWLEN 96
#define ERR_LEARN_TIMECNT 97
#define ERR_LEARN_TC_LEN 98


#define ERR_OPENSOCKET 100
#define ERR_BINDSOCKET 101
#define ERR_FINDHOST 103
#define ERR_CONNECT 104
#define ERR_SEND 105
#define ERR_RECV 106
#define ERR_BINDWEB 107
#define ERR_DEVICEUNKNOWN 108


#define FATAL 1
#define IR 2
#define IRTIMEOUT 3

void GetError(int res, char st[]);
