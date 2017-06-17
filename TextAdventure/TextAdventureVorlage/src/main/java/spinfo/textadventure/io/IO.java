package spinfo.textadventure.io;

import java.io.File;
import java.io.IOException;
import java.util.List;

import spinfo.textadventure.InvalidGameException;
import spinfo.textadventure.data.Place;
import spinfo.textadventure.data.Player;
import spinfo.textadventure.data.World;

public interface IO {

	/**
	 * Lädt die Liste aller Orts-Details aus der places-Datei im
	 * Spiel-Verzeichnis. Tritt dabei ein Fehler auf, wird eine
	 * InvalidGameException geworfen.
	 */
	public List<Place> loadPlaces() throws InvalidGameException;

	/**
	 * Erzeugt eine World-Instanz aus den Informationen der World-Datei im
	 * Spiel-Verzeichnis und der Liste aller Orte. Tritt dabei ein Fehler auf,
	 * wird eine InvalidGameException geworfen.
	 */
	public World loadWorld(List<Place> loadedPlaces) throws InvalidGameException;

	/**
	 * Speichert das Spiel im Spiel-Verzeichnis
	 */
	public void saveGame(Player player) throws IOException;

	/**
	 * Lädt das Spiel aus dem Spiel-Verzeichnis. Falls loadSaveGame den Wert
	 * true hat, soll der gespeicherte Spielstand geladen werden, sonst der
	 * initiale Spielstand.
	 */
	public Player loadGame(boolean loadSaveGame) throws IOException;

	/**
	 * Setzt das Spiel-Verzeichnis.
	 * 
	 * @param gameDirectory
	 */
	public void setGameDirectory(File gameDirectory);

}
