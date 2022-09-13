/**
 * Servidor de citações ouvindo na porta 6017.
 *
 * @author Gagne, Galvin, Silberschatz
  * Fundamentos de Sistemas Operacionais, Nona Edição
 * Copyright John Wiley & Sons - 2013
 */
 
import java.net.*;
import java.io.*;

public class QuoteServer
{
	static final int PORT = 6017;

	private static final String[] fortunes = { 
							"Buy Low and Sell High",
							"Eat Your Vegetables",
							"Good Fences Make Good Neighbors",
							"Never Underestimate Your Competition",
							"A Clean Camp is a Happy Camp",
							"Write tests before writing code.",
							"Do no evil."
						};
                                                
	public static void main(String[] args) throws IOException {
		Socket client = null;
		ServerSocket sock = null;

		try {
			sock = new ServerSocket(PORT);
			// agora procura conexões
			while (true) {
				client = sock.accept();

				// temos uma conexão
				PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
				// grava a data no socket
				pout.println(fortunes[(int)(java.lang.Math.random() * fortunes.length)] );

				pout.close();
				client.close();
			}
		}
		catch (IOException ioe) {
				System.err.println(ioe);
		}
		finally {
			if (sock != null)
				sock.close();
			if (client != null)
				client.close();
		}
	}
}
