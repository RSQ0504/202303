import javax.swing.*;
import javax.swing.colorchooser.AbstractColorChooserPanel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ColorPickerWithSliders {
    private static JColorChooser colorChooser;
    private static JLabel redLabel, greenLabel, blueLabel;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            createAndShowGUI();
        });
    }

    private static void createAndShowGUI() {
        JFrame frame = new JFrame("Color Picker with Sliders");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 400);

        JPanel panel = new JPanel();
        frame.add(panel);

        colorChooser = new JColorChooser(Color.BLACK);
        colorChooser.setPreviewPanel(new JPanel()); // Disable the default color preview panel

        // Add a custom color panel with RGB sliders
        AbstractColorChooserPanel customPanel = new AbstractColorChooserPanel() {
            private JSlider redSlider, greenSlider, blueSlider;

            @Override
            public void updateChooser() {
                Color color = getColorSelectionModel().getSelectedColor();
                if (color != null) {
                    redSlider.setValue(color.getRed());
                    greenSlider.setValue(color.getGreen());
                    blueSlider.setValue(color.getBlue());
                }
            }

            @Override
            protected void buildChooser() {
                setLayout(new GridLayout(3, 2));

                redSlider = createSlider("Red", 0, 255, 0);
                greenSlider = createSlider("Green", 0, 255, 0);
                blueSlider = createSlider("Blue", 0, 255, 0);

                add(redSlider);
                add(greenSlider);
                add(blueSlider);

                redSlider.addChangeListener(new ChangeListener() {
                    @Override
                    public void stateChanged(ChangeEvent e) {
                        updateColor();
                    }
                });

                greenSlider.addChangeListener(new ChangeListener() {
                    @Override
                    public void stateChanged(ChangeEvent e) {
                        updateColor();
                    }
                });

                blueSlider.addChangeListener(new ChangeListener() {
                    @Override
                    public void stateChanged(ChangeEvent e) {
                        updateColor();
                    }
                });
            }

            @Override
            public String getDisplayName() {
                return "RGB Sliders";
            }

            @Override
            public Icon getSmallDisplayIcon() {
                return null;
            }

            @Override
            public Icon getLargeDisplayIcon() {
                return null;
            }
        };

        colorChooser.addChooserPanel(customPanel);
        panel.add(colorChooser);

        redLabel = createValueLabel("Red: 0");
        greenLabel = createValueLabel("Green: 0");
        blueLabel = createValueLabel("Blue: 0");

        panel.add(redLabel);
        panel.add(greenLabel);
        panel.add(blueLabel);

        JButton resetButton = new JButton("Reset");
        resetButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                colorChooser.setColor(Color.BLACK);
            }
        });

        panel.add(resetButton);

        frame.setVisible(true);
    }

    private static JSlider createSlider(String label, int min, int max, int initial) {
        JSlider slider = new JSlider(JSlider.HORIZONTAL, min, max, initial);
        slider.setPaintLabels(true);
        slider.setPaintTicks(true);
        slider.setMajorTickSpacing(50);
        slider.setMinorTickSpacing(10);
        slider.setBorder(BorderFactory.createTitledBorder(label));

        return slider;
    }

    private static JLabel createValueLabel(String text) {
        JLabel label = new JLabel(text);
        label.setHorizontalAlignment(JLabel.CENTER);
        return label;
    }

    private static void updateColor() {
        int red = colorChooser.getColor().getRed();
        int green = colorChooser.getColor().getGreen();
        int blue = colorChooser.getColor().getBlue();

        redLabel.setText("Red: " + red);
        greenLabel.setText("Green: " + green);
        blueLabel.setText("Blue: " + blue);
    }
}
