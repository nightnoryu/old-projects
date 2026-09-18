import matplotlib.pyplot as plt

from random_walk import RandomWalk


def main():
    """Main function"""
    # Создание случайного блуждания
    rw = RandomWalk(50000)
    rw.fill_walk()

    # Отображение блуждания
    plt.figure(figsize=(10, 6))
    point_numbers = list(range(rw.num_points))
    plt.scatter(rw.x_values, rw.y_values, c=point_numbers, cmap=plt.cm.Purples, edgecolors='none', s=1)

    # Выделение первой и последней точек
    plt.scatter(0, 0, c='green', edgecolors='none', s=100)
    plt.scatter(rw.x_values[-1], rw.y_values[-1], c='green', edgecolors='none', s=100)

    # Удаление осей
    plt.gca().get_xaxis().set_visible(False)
    plt.gca().get_yaxis().set_visible(False)

    plt.show()


# Entry point
if __name__ == "__main__":
    main()
