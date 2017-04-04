#!/usr/bin/python

"""
Author: Jonathan Nicolosi
Date: 11/29/2016
Class: CS372
Project 2

File Transfer Client

Usage: python ftclient.py <SERVER_HOST> <SERVER_PORT> <COMMAND> <DATA_PORT> <FILENAME>

https://docs.python.org/2/howto/sockets.html
"""

import socket
import sys
from struct import *
import os.path


def checkPort(port):
    if int(port) < 1024 or int(port) > 65535:
        return -1
    else:
        return int(port)


def portError():
    print "Port number out of range."

# takes a hostname and port number
# connects to the server
def initiateConnection(host, port):
	if checkPort(port) < 1:
		portError()
		sys.exit(0)
	   
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect((host, port))

	if s < 0:
		print "Error connecting to " + host + ":" + str(port)
		sys.exit(0)
	return s


def sendMsg(sockfd, outgoing):
    size = len(outgoing)            
    try:
        # https://docs.python.org/2/library/struct.html
        #*****************************************************************
        data = pack('I', size)          
        sockfd.send(data)               
        #*****************************************************************
        sockfd.send(outgoing)           
    except:
        print "An Unknown Error Occurred"
        d.close()
        c.close()
        sys.exit(1)

def receiveMessage(sockfd):
    try:
        data = sockfd.recv(4)               
        recvsize = unpack('I', data)        
        incoming = sockfd.recv(recvsize[0]) 
        return incoming			
    except:
        print "An Unknown Error Occurred"
        d.close()
        c.close()
        sys.exit(1)

def sendPort(sockfd, port):
    try:
        data = pack('I', port)
        sockfd.send(data)
    except:
        print "An Unknown Error Occurred"
        d.close()
        c.close()
        sys.exit(1)

def makeRequest(sockfd, port, outgoing):
    try:
        sendMsg(sockfd, outgoing)
        sendPort(sockfd, port)
    except:
        print "An Unknown Error Occurred"
        d.close()
        c.close()
        sys.exit(1)

def receiveFile(socket, totalfile):
    filename, file_ext = os.path.splitext(totalfile)

    print "Initiating Transfer Request"
    file = receiveMessage(socket)

    overwrite = True
	
    # http://stackoverflow.com/questions/82831/check-whether-a-file-exists-using-python
    #***********************************************************************************
    if os.path.isfile(totalfile):
    #***********************************************************************************
        # prompt for overwrite
        choice = raw_input("File Already Exists; Overwrite? (y/n)")
        if choice == 'y':
            overwrite = True
        else:
            overwrite = False
         

    if overwrite == False:
        filename = filename + "_copy"
        totalfile = filename + file_ext
		
    #  http://learnpythonthehardway.org/book/ex16.html
    #**************************************************
    target_file = open(totalfile, 'w')
    target_file.write(file)
    #**************************************************

    print("Transfer Complete")

if len(sys.argv) < 5 or len(sys.argv) > 6:
    print "\nUsage:\n $ python ftclient.py [SERVER_HOST] [SERVER_PORT] [COMMAND] [DATA_PORT] <FILENAME>\n<FILENAME> is an optional parameter\n"
    sys.exit(0)
else:
    #Connect to server
    c = initiateConnection(sys.argv[1], int(sys.argv[2]))

    #Get command from arguments
    command = sys.argv[3]

    #Send request
    makeRequest(c, int(sys.argv[4]), command)

    #Open Data Connection
    d = initiateConnection(sys.argv[1], int(sys.argv[4]))
    
    #Get File
    if command == "-g":
        try:
            filename = sys.argv[5]	#Get filename
        except:
            print "Error:\n  <FILENAME> Parameter Required with [-g] Command"
            c.close()
            d.close()
            sys.exit(0)

        #Send filename
        makeRequest(c, int(sys.argv[4]), filename)

        #Get response
        incoming = receiveMessage(c)

        #Use data connection for receiving file
        if incoming == "DATA":
            receiveFile(d, filename)
        else:
            print "Requested File Does Not Exist; Please Try Again"

    
    else:
        #Get message on control connection
        incoming = receiveMessage(c)
        #If Data Connection is ready, receive data
        if incoming == "DATA":
            incoming = receiveMessage(d)	
            print incoming

        print incoming	

   
    d.close()

    print ("Closing Control Connection to Server")
    
    c.close()