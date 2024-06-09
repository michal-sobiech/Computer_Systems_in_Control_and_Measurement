import matplotlib.pyplot as plt
import numpy as np
from matplotlib.offsetbox import OffsetImage, AnnotationBbox
import time
from collections import deque

class RadarPlotter:
    def __init__(self, *, number_of_drawn_points: int, path_to_radar_image: str) -> None:
        self.radar_img = plt.imread(path_to_radar_image)
        self.radar_position = (0, 0)
        self.number_of_drawn_points = number_of_drawn_points
        self.fig = None
        self.ax = None
        self.radarbox = AnnotationBbox(OffsetImage(self.radar_img, zoom=0.05), self.radar_position, frameon=False, pad=0.0, xycoords='data', boxcoords="data")
        self.points: deque[tuple[int, int]] = deque()

    def plot(self) -> None:
        if (not self.instantiated_plot()):
            self.fig, self.ax = plt.subplots(subplot_kw={'projection': 'polar'})
            self.draw_axes()
            if not plt.isinteractive(): 
                plt.ion()
        self.replot()

    def add_point(self, angle:int, distance:int):
        self.points.append((angle, distance))
        if (self.number_of_drawn_points < len(self.points)):
            self.points.popleft()        

    
    def instantiated_plot(self) -> bool:
        return self.fig and self.ax

    def draw_radar(self) -> None:
        self.ax.add_artist(self.radarbox)

    def replot(self):
        self.ax.clear()
        self.draw_axes()
        # Drawing points
        if len(self.points) > 0:
            points, distances = zip(*self.points)
        else:
            points, distances = [], []
        self.ax.scatter(np.radians(points), distances, c='blue', s=20)
        for angle, distance in self.points:
            angle_in_radians = np.radians(angle)
            label = f"{distance:.2f}"
            self.ax.annotate(label, (angle_in_radians, distance), textcoords="offset points", xytext=(0, 5), ha='center', fontsize=6)
        plt.draw()
        plt.pause(0.1)
    
    def draw_axes(self) -> None:
        self.ax.set_theta_offset(np.pi / 2)  # Obracamy wykres tak, aby 0 stopni był na górze
        self.ax.set_theta_direction(-1)  # Kierunek przeciwny do ruchu wskazówek zegara
        self.draw_radar()
        self.ax.set_rlabel_position(90)
        self.ax.set_yticklabels([])  # Usuwamy etykiety odległości
        self.ax.grid(True)

# plotter = RadarPlotter(number_of_drawn_points=100, path_to_radar_image="radar.png")
# plotter.plot()


# for i in range(10):  # Symulacja 10 aktualizacji
#     # Dodanie nowego punktu
#     nowy_kąt = i * 20
#     nowa_odległość = np.random.uniform(1, 10)
#     plotter.add_point(nowy_kąt, nowa_odległość)
#     plotter.plot()
#     time.sleep(1)
    

