import java.util.*;

public class AstrologicalSign {
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        int Q = stdin.nextInt();
        for (int iter = 0; iter < Q; iter++) {
            int day = stdin.nextInt();
            String month = stdin.next();
            switch (month) {
                case "Jan":
                    if (day <= 20) {
                        System.out.println("Capricorn");
                    }
                    else {
                        System.out.println("Aquarius");
                    }
                    break; 
                case "Feb":
                    if (day <= 19) {
                        System.out.println("Aquarius");
                    } else {
                        System.out.println("Pisces");
                    }
                    break;
                case "Mar":
                    if (day <= 20) {
                        System.out.println("Pisces");
                    } else {
                        System.out.println("Aries");
                    }
                    break;
                case "Apr":
                    if (day <= 20) {
                        System.out.println("Aries");
                    } else {
                        System.out.println("Taurus");
                    }
                    break;
                case "May":
                    if (day <= 20) {
                        System.out.println("Taurus");
                    } else {
                        System.out.println("Gemini");
                    }
                    break;
                case "Jun":
                    if (day <= 21) {
                        System.out.println("Gemini");
                    } else {
                        System.out.println("Cancer");
                    }
                    break;
                case "Jul":
                    if (day <= 22) {
                        System.out.println("Cancer");
                    } else {
                        System.out.println("Leo");
                    }
                    break;
                case "Aug":
                    if (day <= 22) {
                        System.out.println("Leo");
                    } else {
                        System.out.println("Virgo");
                    }
                    break;
                case "Sep":
                    if (day <= 21) {
                        System.out.println("Virgo");
                    } else {
                        System.out.println("Libra");
                    }
                    break;
                case "Oct":
                    if (day <= 22) {
                        System.out.println("Libra");
                    } else {
                        System.out.println("Scorpio");
                    }
                    break;
                case "Nov":
                    if (day <= 22) {
                        System.out.println("Scorpio");
                    } else {
                        System.out.println("Sagittarius");
                    }
                    break;
                case "Dec":
                    if (day <= 21) {
                        System.out.println("Sagittarius");
                    } else {
                        System.out.println("Capricorn");
                    }
                    break;
            }
        }
        stdin.close(); 
        return; 
    }
}