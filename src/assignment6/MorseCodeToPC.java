package assignment6;

import java.util.Scanner;

import jssc.SerialPortException;

public class MorseCodeToPC {
	public static void main(String[] args) throws SerialPortException {		
		// TODO:  Complete program to show "training messages" and decoded Morse code
		SerialComm port = new SerialComm("/dev/cu.usbserial-DN02AZZ5");
		Scanner in = new Scanner(System.in);
		
		// declaring string to hold incoming letters from Arduino
		String buff = "";
		
		while(true)
		{
			//reads from arduino
			while (port.available())
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
			
			//writes to Arduino
			/*if (in.hasNext())
			{
				String S = in.nextLine();
				int size = S.length();
				for (int i = 0; i < size; i++)
					port.writeByte((byte) S.charAt(i));
			}*/
		}
	}

}
