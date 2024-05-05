#include <iostream>
#include <list>
#include "targetver.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "stdafx.h"
#include <winsock.h>

using namespace std;

// pointers

//struct WSASocket {
//
//    WORD wVersion;
//    WORD wHighversion;
//    char szDEescription[WSADESCRIPTION_LEN + 1];
//    char szSystemStatus[WSASYS_STATUS_LEN + 1];
//    unsigned short iMaxSockets;
//    unsigned short iMaxUdpDg;
//    char FAR* IpVendorInfo;
//};




int main (int argc, char* argv[]) {

WSADATA wsaData;
int wsaerr;
WORD wVersionRequested = MAKEWORD(2, 2);
wsaerr = WSAStartup(wVersionRequested, &wsaData);

if (wsaerr != 0) {
    cout << "The Winsock dll not found!" << endl;
}
else {
    cout << "The Winsock dll found!" << endl;
    cout << "The status: " << wsaData.szSystemStatus << endl;
}

// create socket

SOCKET serverSocket = INVALID_SOCKET;
serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
if (serverSocket == INVALID_SOCKET) {
    cout << "Error socket(): " << WSAGetLastError() << endl;
    WSACleanup();
    return 0;
}
else {
    cout << "socket() is OK!" << endl;
    }

//WSACleanup();

// bind 

sockaddr_in service;

service.sin_family = AF_INET;
InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
service.sin_port = htons(55555);

if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR){
    cout << "bind() failed: " << WSAGetLastError() << endl;
    closesocket(serverSocket);
    WSACleanup();
    return 0;
    }
else {
    cout << "bind() is OK!" << endl;

    }


// listen

if (listen(serverSocket, 1) == SOCKET_ERROR) {
    cout << "listen(): Error listining on socket" << WSAGetLastError() << endl;
}
else {
    cout << "listen() is OK! I'm waiting for connections!" << endl;

}

// accept

SOCKET clientSocket;
clientSocket = accept(serverSocket, NULL, NULL);
if (clientSocket == INVALID_SOCKET) {
    cout << "accept failed: " << WSAGetLastError() << endl;
    WSACleanup();
    return -1;
}

else {

    cout << " Socket ServerSocket is accessed clientSocket" << endl;
}


// TSP transmisition (recieve)

char recivebuffer[200];
int byteCout = recv(clientSocket, recivebuffer, sizeof(recivebuffer), 0);
if (byteCout < 0) {
    cout << "Client: errror " << WSAGetLastError() << endl;
}

else {
    cout << "Recieved data: " << recivebuffer << endl;

}


    system("pause>0");
    return 0;
}

