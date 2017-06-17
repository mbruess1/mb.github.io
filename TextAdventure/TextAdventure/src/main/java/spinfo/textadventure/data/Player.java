package spinfo.textadventure.data;

import java.util.List;

public interface Player {
	
	/**
	 * Gibt die erste Koordinate des Spielers in der Welt zurück.
	 * @return
	 */
	public int getX();
	
	/**
	 * Gibt die zweite Koordinate des Spielers in der Welt zurück.
	 * @return
	 */
	public int getY();
	
	/**
	 * Gibt die Liste aller Bedingungen, die vom Spieler erfüllt wurden, zurück.
	 * @return
	 */
	public List<String> getConditions();
	
	/**
	 * Setzt die Liste aller Bedingungen.
	 * @param conditions
	 */
	public void addConditions(List<String>conditions);
	
	/**
	 * Muss von der Runtime-Implementation aufgerufen werden, um den Spieler
	 * in die entsprechende Richtung zu bewegen.
	 * @param direction
	 * @param world
	 */
	public void move(String direction, World world);
	
	/**
	 * Gibt true zurück, wenn der entsprechende Raum bereits vom Spieler
	 * betreten wurde, sonst false.
	 * @param roomName
	 * @return
	 */
	public boolean entered(String roomName);

	/**
	 * Gibt die Liste aller Räume zurück, die bereits vom
	 * Spieler betreten wurden.
	 * @return
	 */
	public List<String> getEnteredRooms();

}
