import java.util.Scanner;
import java.io.OutputStream;
import java.io.PrintStream;

class Main {
    static class LineCounter extends OutputStream {
        int lines = 0;
        @Override public void write(int value) {
            if (value == '\n') ++lines;
        }
    }
    public static void main(String[] args) {
        LineCounter output = new LineCounter();
        PrintStream original = System.out;
        System.setOut(new PrintStream(output));
        // --8<-- [start:core]
        final int N = 100000;
        for (int i = 0; i < N; ++i) {
            System.out.println("hello world");
        }
        // --8<-- [end:core]
        System.out.flush();
        System.setOut(original);
        System.out.println(output.lines);
    }
}
