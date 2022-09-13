/**
 * Um cliente de eco. O cliente insere dados no servidor e o
  * servidor ecoa os dados de volta para o cliente.
 *
 * Fundamentos de Sistemas Operacionais, Nona Edição
 * Copyright John Wiley & Sions - 2013
 */
import java.net.*;
import java.io.*;

public class EchoClient
{
	public static final int DEFAULT_PORT = 6007;
	
	public static void main(String[] args) throws IOException {
		if (args.length != 1) {
			System.err.println("Usage: java EchoClient <echo server>");
			System.exit(0);
		}
		
		BufferedReader networkBin = null;	// o leitor da rede
		PrintWriter networkPout = null;		// o gravador da rede
		BufferedReader localBin = null;		// o leitor do teclado local 
		Socket sock = null;			// o socket
		
		try {
			sock = new Socket(args[0], DEFAULT_PORT);
			
			/* configura os canais de comunicação necessários*/
			networkBin = new BufferedReader(new InputStreamReader(sock.getInputStream()));
			localBin = new BufferedReader(new InputStreamReader(System.in));
			
			/**
			 * um PrintWriter nos permite usar println() com o I/O de socket comum 
			 * "true" indica uma descarga automatic do fluxo.
			 * O fluxo é descarregado com uma chamada a println()
			 */
			networkPout = new PrintWriter(sock.getOutputStream(),true);
			
			/**
			 * Lê no teclado e envia para o servidor de eco.
			 ** Abandona a leitura quando o cliente insere um ponto "."
			 */
			boolean done = false;
			while (!done) {
				String line = localBin.readLine();
				if (line.equals("."))
					done = true;
				else {
					networkPout.println(line);
					System.out.println("Server: " + networkBin.readLine());
				}
			}
		}
		catch (IOException ioe) {
			System.err.println(ioe);
		}
		finally {
			if (networkBin != null)
				networkBin.close();
			if (localBin != null)
				localBin.close();
			if (networkPout != null)
				networkPout.close();
			if (sock != null)
				sock.close();
		}
	}
}
