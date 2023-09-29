import java.io.File;

import javax.sound.sampled.*;

public class read_wave {

    private static int sampleSize;
    private static int sampleRate;
    private static byte[] audioData;

    public static void readWavFile(String filePath) {
        try {
            // Open the audio file
            AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(new File(filePath));
            AudioFormat audioFormat = audioInputStream.getFormat();
            
            sampleSize = audioFormat.getSampleSizeInBits() / 8;
            sampleRate = (int) audioFormat.getSampleRate();
            int numFrames = (int) audioInputStream.getFrameLength();
            int numBytes = numFrames * sampleSize;

            audioData = new byte[numBytes];
            audioInputStream.read(audioData);

        } catch (Exception e) {
            e.printStackTrace();

        }
    }
}
