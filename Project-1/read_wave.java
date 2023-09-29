import java.awt.*;
import java.io.File;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import javax.sound.sampled.*;
import javax.swing.*;

public class read_wave  extends JPanel {

    private static int bytes_per_sample;
    private static int sample_rate;
    private static byte[] data_c1;
    private static byte[] data_c2;
    private static AudioFormat audioFormat;


    public read_wave(String filePath) {
        try {
            // Open the audio file
            AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(new File(filePath));
            audioFormat = audioInputStream.getFormat();
            
            bytes_per_sample = audioFormat.getSampleSizeInBits() / 8;
            sample_rate = (int) audioFormat.getSampleRate();
            int frame_num = (int) audioInputStream.getFrameLength();
            int byte_num_per_channel = frame_num * bytes_per_sample;

            data_c1 = new byte[byte_num_per_channel];
            data_c2 = new byte[byte_num_per_channel];
            byte[] data = new byte[byte_num_per_channel*2];
            audioInputStream.read(data);

            for (int i = 0; i < byte_num_per_channel; i+=bytes_per_sample) {
                for(int j = 0; j<bytes_per_sample;j++){
                    data_c1[i+j] = data[i * 2 + j];
                    data_c2[i+j] = data[i * 2 + bytes_per_sample + j];
                }
            }

        } catch (Exception e) {
            e.printStackTrace();

        }
    }

    public void draw(){
        repaint(); 
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        int w = getWidth();
        int h = getHeight();
        int w_drawing = getWidth();
        int h_drawing = getHeight()-40;
        g.setColor(Color.BLACK);
        g.fillRect(0, 0, w, h);

        int sample_num = data_c1.length / bytes_per_sample;
        double unit_x = (double) w_drawing / sample_num;
        double unit_y = (double) h_drawing / (1 << (bytes_per_sample * 8 - 1));

        for (int i = 0; i < sample_num - 1; i++) {
            int x1 = (int) (i * unit_x);
            int x2 = (int) ((i + 1) * unit_x);
            int y1;
            int y2;
            if(audioFormat.isBigEndian()){
                y1 = (int) (ByteBuffer.wrap(data_c1, i * bytes_per_sample, bytes_per_sample).order(ByteOrder.BIG_ENDIAN).getShort() * unit_y);
                y2 = (int) (ByteBuffer.wrap(data_c1, (i + 1) * bytes_per_sample, bytes_per_sample).order(ByteOrder.BIG_ENDIAN).getShort() * unit_y);
            }else{
                y1 = (int) (ByteBuffer.wrap(data_c1, i * bytes_per_sample, bytes_per_sample).order(ByteOrder.LITTLE_ENDIAN).getShort() * unit_y);
                y2 = (int) (ByteBuffer.wrap(data_c1, (i + 1) * bytes_per_sample, bytes_per_sample).order(ByteOrder.LITTLE_ENDIAN).getShort() * unit_y);
            }

            g.setColor(Color.GREEN);
            g.drawLine(x1, h_drawing / 4 + y1 + 40, x2, h_drawing / 4 + y2 + 40);

            if(audioFormat.isBigEndian()){
                y1 = (int) (ByteBuffer.wrap(data_c2, i * bytes_per_sample, bytes_per_sample).order(ByteOrder.BIG_ENDIAN).getShort() * unit_y);
                y2 = (int) (ByteBuffer.wrap(data_c2, (i + 1) * bytes_per_sample, bytes_per_sample).order(ByteOrder.BIG_ENDIAN).getShort() * unit_y);
            }else{
                y1 = (int) (ByteBuffer.wrap(data_c2, i * bytes_per_sample, bytes_per_sample).order(ByteOrder.LITTLE_ENDIAN).getShort() * unit_y);
                y2 = (int) (ByteBuffer.wrap(data_c2, (i + 1) * bytes_per_sample, bytes_per_sample).order(ByteOrder.LITTLE_ENDIAN).getShort() * unit_y);
            }

            g.setColor(Color.GREEN);
            g.drawLine(x1, 3 * h_drawing / 4 + y1 + 40, x2, 3 * h_drawing / 4 + y2 + 40);
        }

        g.setColor(Color.white);
        g.drawString("total number of the samples: " + sample_num, 30, 20);
        g.drawString("sampling frequency: " + sample_rate + " Hz", 30, 40);
    }
}
