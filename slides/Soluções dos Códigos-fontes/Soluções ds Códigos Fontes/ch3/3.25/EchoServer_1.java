/**
 * Um servidor de eco ouvindo na porta 6007. Esse servidor l� no cliente
 * e retorna o resultado. 
 *
 * Fundamentos de Sistemas Operacionais, Nona Edi��o
 * Copyright John Wiley & Sions - 2013
 */

import java.net.*;
import java.io.*;

public class  EchoServer
{
	public static final int DEFAULT_PORT = 6007;
    public static final int BUFFER_SIZE = 256;
    
    public static void process(Socket client) throws java.io.IOException {
		byte[] buffer = new byte[BUFFER_SIZE];
		InputStream  fromClient = null;
		OutputStream toClient = null;
		
		try {
			/**
			 * obt�m os fluxos de entrada e sa�da associados ao socket.
			 */
			fromClient = new BufferedInputStream(client.getInputStream());
			toClient = new BufferedOutputStream(client.getOutputStream());
			int numBytes;
			
			/** entra em loop continuo at� o cliente fechar a conex�o */
			while ( (numBytes = fromClient.read(buffer)) != -1) {
				toClient.write(buffer,0,numBytes);
				toClient.flush();
			}
   		}
		catch (IOException ioe) {
			System.err.println(ioe);
		}
		finally {
			// fecha os fluxos e o socket
			if (fromClient != null)
				fromClient.close();
			if (toClient != null)
				toClient.close();
			if (client != null)
				client.close();
		}
	}

	
    public static void main(String[] args) throws IOException {
		ServerSocket sock = null;
		
		try {
			// estabelece o socket
			sock = new ServerSocket(DEFAULT_PORT);
			
			while (true) {
				/**
				 * agora procura conex�es */*/
				process(sock.accept());
			}
		}
		catch (IOException ioe) { }
		finally {
			if (sock != null)
				sock.close();
		}
	}
}
