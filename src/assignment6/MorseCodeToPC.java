package assignment6;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

import jssc.SerialPortException;

public class MorseCodeToPC {
	public static void main(String[] args) {		

		// TODO:  Complete program to show "training messages" and decoded Morse code
		SerialComm port;
		try {
			port = new SerialComm("/dev/cu.usbserial-DN02AZZ5");

			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

			// declaring string to hold incoming letters from Arduino
			String buff = "";

			while(true)
			{
				//writes to Arduino

				try {
					if (in.ready())
					{
						//System.out.println(in.hasNext());
						String S = in.readLine();
						int size = S.length();
						for (int i = 0; i < size; i++)
							port.writeByte((byte) S.charAt(i));
					}
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}


				//reads from arduino
				if (port.available())
				{
					char c = port.readByte();
					if (c == '#') // prints until readByte finds another #
					{
						System.out.println();
						c = port.readByte();
						while (c != '#')
						{
							System.out.print(c);
							c = port.readByte();
						}
						//System.out.println();
					}

					//if its a space, clear word buffer
					else if (c == ' ')
					{

						System.out.print("\nWord: " + buff);
						buff = "";
					}

					//otherwise add to word buffer
					else
					{
						System.out.print(" '" + c + "'");
						buff = buff + c;
					}
				}
			}
		} catch (SerialPortException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

}
