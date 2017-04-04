import java.net.*;
import java.io.*;
import java.io.BufferedReader;
import java.util.Scanner;
//Source http://docs.oracle.com/javase/tutorial/networking/sockets/clientServer.html
public class chatserve {
	
	public static boolean gotclienthandle = false;
	
	public static String serverhandle = "";
	public static String clienthandle = "";
	
	//make sure the client's handle is no longer than 10 characters. if it is, truncate it.
	public static String truncate(String ch){
		
		if(ch.length() > 10)
			return ch.substring(0,10);
		return ch;
		
		
	}
	
	
    public static void main(String[] args) throws IOException {
         
        if (args.length != 1) {
            System.err.println("Usage: java chatserve <port number>");
            System.exit(1);
        }
 
        int portNumber = Integer.parseInt(args[0]);
		System.out.print("Enter server handle: ");
	
	BufferedReader consoleInput =  new BufferedReader(new InputStreamReader(System.in));
	
		try {  
			//GET THE SERVERS HANDLE
			serverhandle = consoleInput.readLine();
			if(serverhandle.equals("\\quit")){
					System.exit(0);
				}
			if(serverhandle.length() > 10){
				serverhandle = serverhandle.substring(0,10);
			}
			System.out.println("Welcome " + serverhandle);
			System.out.println("***Awaiting incoming connections***");
			
		} catch(Exception e) {  //Invalid handle.
			System.err.println("\nInvalid handle input. ");
			return;  //close program
		}
	
	//Outer loop runs until the server enters \quit
	while(true){
		//create the socket
        try ( 
            ServerSocket serverSocket = new ServerSocket(portNumber);
            Socket clientSocket = serverSocket.accept();
            PrintWriter out =
                new PrintWriter(clientSocket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(
                new InputStreamReader(clientSocket.getInputStream()));
        ) {
         
            String inputLine, outputLine;
             
            // Initiate conversation with client
            
			
            outputLine = "Connected to " + serverhandle;
            out.println(outputLine);
			//runs until the client types \quit
            while ((inputLine = in.readLine()) != null) {
				
				if(inputLine.equals("\\quit")){
					System.out.println("Client disconnected");
					System.out.println("***Awaiting incoming connections***");
					clientSocket.close();
					gotclienthandle = false;
					break;
				}
				//for the first run of the loop
				if(gotclienthandle == false){
					clienthandle = inputLine;
					System.out.println(truncate(clienthandle) + " has connected.");
					out.println(truncate(clienthandle) + "> ");
					gotclienthandle = true;
				}
				//every subsequent run of the loop
				else{
					System.out.println(truncate(clienthandle) + "> " + inputLine);
					System.out.print(serverhandle + "> ");
					outputLine = consoleInput.readLine();
					if(outputLine.equals("\\quit")){
						System.exit(0);
				}
					out.println(serverhandle + "> " + outputLine + "\n" + truncate(clienthandle) + "> ");
					}


            }
        } catch (IOException e) {
            System.out.println("Exception caught when trying to listen on port "
                + portNumber + " or listening for a connection");
            System.out.println(e.getMessage());
        }
	}
		
    }
}