package spinfo.textadventure;

import java.io.File;

import spinfo.textadventure.classes.IOClass;
import spinfo.textadventure.io.IO;

public class TextAdventure {

	public static IO getIO() {
		File gameDirectory = new File("games/adventure");
		IOClass io = new IOClass();
		io.setGameDirectory(gameDirectory);
		return io;
	}

	public static void main(String[] args) {
		try {
			IO io = getIO();
			Runtime runtime = new Runtime();
			runtime.initialize(io);
			runtime.play();
		} catch (InvalidGameException e) {
			e.printStackTrace();
		}
	}
}
