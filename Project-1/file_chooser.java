import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

public class file_chooser {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Part");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 400);

        JButton button_wav = new JButton("Open .wav File");
        button_wav.setBounds(150, 70, 150, 30);

        JButton button_tif = new JButton("Open .tif File");
        button_tif.setBounds(150, 120, 150, 30);

        JFileChooser file_window_wav = new JFileChooser();

        FileNameExtensionFilter filter_wav = new FileNameExtensionFilter("WAV", "wav");
        file_window_wav.setFileFilter(filter_wav);


        JFileChooser file_window_tif = new JFileChooser();

        FileNameExtensionFilter filter_tif = new FileNameExtensionFilter("TIF", "tif");
        file_window_tif.setFileFilter(filter_tif);

        JPanel panel = new JPanel();
        panel.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10)); 
        panel.add(button_wav);
        panel.add(button_tif);
        frame.add(panel);
        frame.setVisible(true);

        button_wav.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int check = file_window_wav.showOpenDialog(null);
                if (check == JFileChooser.APPROVE_OPTION) {
                    File file = file_window_wav.getSelectedFile();
                    System.out.println("Selected .wav File: " + file.getPath());
                    frame.getContentPane().removeAll();
                    read_wave reader = new read_wave(file.getPath());
                    reader.draw();
                    frame.add(reader);
                    frame.revalidate();
                    frame.repaint();
                } else {
                    System.out.println("Cancel");
                }
            }
        });

        button_tif.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int check = file_window_tif.showOpenDialog(null);
                if (check == JFileChooser.APPROVE_OPTION) {
                    File file = file_window_tif.getSelectedFile();
                    System.out.println("Selected .tif File: " + file.getPath());
                } else {
                    System.out.println("cancel");
                }
            }
        });
    }
}
