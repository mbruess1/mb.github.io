package spinfo.textadventure.data;

public interface World {

	/**
	 * Zum Setzen der Orts-Details in der Welt
	 * 
	 * @param places
	 */
	public void setPlaces(Place[][] places);

	/**
	 * Gibt die Karte auf der Konsole aus. Die Position des Spielers ist durch
	 * die übergebenen Parameter definiert.
	 */
	public void printMap(int playerX, int playerY);

	/**
	 * Gibt den Ort an der definierten Position zurück, oder null, falls nicht
	 * vorhanden.
	 */
	public Place getPlace(int x, int y);

}
