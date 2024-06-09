from argparse import ArgumentParser
from matplotlib import pyplot
import sys
import os
from typing import List

def read_file_lines(file):
    lines = []
    with open(file, 'r') as handle:
        for line in handle:
            lines.append(line)
    return lines

def file_lines_to_data(file_lines:list):
    data = []
    for line in file_lines:
        split_line = line.split(',')
        data.append(float(split_line[3]))
    return data

def read_file_data(file: str):
    return file_lines_to_data(read_file_lines(file))

def filter_data(data: list, filtering_function: callable):
    filtered_data = []
    for e in data:
        if filtering_function(e):
            filtered_data.append(e)
    return filtered_data

def draw_histogram(data: list, label: str, color: str):
    pyplot.hist(data, bins=100, label=label, alpha=0.5, color=color)
    pyplot.xlabel('Czas dostarczenia [us]')
    pyplot.ylabel('Liczba wystąpień wartości')

def draw_many_charts(charting_func: callable, data_lists: List[list], label_list: List[str]):
    colors = ['red', 'green', 'blue', 'orange']
    for i in range(len(data_lists)):
        data = data_lists[i]
        label = label_list[i]
        color = colors[i]
        charting_func(data=data, label=label, color=color)
    pyplot.legend()

# def draw_plot(data: list, label: str, color: str):
#     x_axis_numbers = range(len(data))
#     pyplot.plot(x_axis_numbers, data, label=label, alpha=0.5, color=color)
#     pyplot.xlabel('Czas dostarczenia [ms]')
#     pyplot.ylabel('Liczba wystąpień wartości')

def get_client_name_from_file_name(file_name: str):
    for letter in file_name:
        if letter.isdigit():
            return f"Klient numer {int(letter)}"

def save_chart():
    pyplot.savefig('file')

def main():
    parser = ArgumentParser()

    parser.add_argument('chart_type')
    parser.add_argument('data_dir')
    parser.add_argument('--file_1')
    parser.add_argument('--file_2')
    parser.add_argument('--file_3')
    parser.add_argument('--file_4')

    args = parser.parse_args()

    chart_type = args.chart_type
    data_dir = args.data_dir
    file_1 = args.file_1
    file_2 = args.file_2
    file_3 = args.file_3
    file_4 = args.file_4

    print(args)

    charting_function = None
    if chart_type == 'histogram':
        charting_function = draw_histogram
    # elif chart_type == 'plot':
    #     charting_function = draw_plot
    else:
        print('Unknown chart type')
        sys.exit(1)

    # A list of lists with data
    data_lists = []

    # For the legend
    label_list = []

    file_list = [file_1, file_2, file_3, file_4]
    for file in file_list:
        if not file:
            continue
        full_file_path = os.path.join(data_dir, file)
        data = read_file_data(full_file_path)
        data = filter_data(
            data=data,
            filtering_function=lambda e: True
        )
        data_lists.append(data)
        label_list.append(get_client_name_from_file_name(file))
    draw_many_charts(
        charting_func=charting_function,
        data_lists=data_lists,
        label_list=label_list
    )
    save_chart()
               
if __name__ == '__main__':
    main()