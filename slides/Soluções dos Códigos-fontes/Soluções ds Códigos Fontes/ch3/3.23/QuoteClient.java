/**
  * DateClient modificado para solicitar uma citação
 * ao servidor de citações.
 *
 * @author Gagne, Galvin, Silberschatz
  * Fundamentos de Sistemas Operacionais, Nona Edição
 * Copyright John Wiley & Sons - 2013
 */
 
import java.net.*;
import java.io.*;

public class QuoteClient
{
	public static void main(String[] args) throws IOException {
		InputStream in = null;
		BufferedReader bin = null;
		Socket sock = null;

		try {
			sock = new Socket("127.0.0.1",6017);
			in = sock.getInputStream();
			bin = new BufferedReader(new InputStreamReader(in));

			String line;
			while( (line = bin.readLine()) != null)
				System.out.println(line);
		}
		catch (IOException ioe) {
				System.err.println(ioe);
		}
                finally {
                    sock.close();
                }
	}
}
