import { useEffect, useRef, useState } from "preact/hooks";
import { Chart as ChartJS, CategoryScale, LinearScale, PointElement, LineElement, Title, Tooltip, Legend, LineOptions } from "chart.js";
import { Line } from "react-chartjs-2";

ChartJS.register(CategoryScale, LinearScale, PointElement, LineElement, Title, Tooltip, Legend);

export const options = {
  responsive: true,
  animation: {
    duration: 0,
  },
  plugins: {
    legend: {
      position: "top" as const,
    },
    title: {
      display: true,
      text: "Chart.js Line Chart",
    },
  },
  scales: {
    y: {
      min: 0,
      max: 500,
    },
  },
};

const labels = ["January", "February", "March", "April", "May", "June", "July"];

export const data = {
  labels,
  datasets: [
    {
      label: "Dataset 1",
      data: [80, 60, 66, 23, 65, 23, 73],
      borderColor: "rgb(255, 99, 132)",
      backgroundColor: "rgba(255, 99, 132, 0.5)",
    },
  ],
};

export function Magnetometer() {
  const [update, setUpdate] = useState<any>(data);

  const chartRef = useRef<typeof Line | null>(null);
  useEffect(() => {
    var socket = new WebSocket("ws://my-esp32.local/ws-api/magnetometer");
    socket.onopen = () => socket.send(JSON.stringify({ cmd: "start", interval: 200 }));
    let max = 0;
    let min = 0;
    socket.onmessage = (event) => {
      setUpdate((d) => {
        const data = JSON.parse(event.data);
        let newData = [...d.datasets[0].data];
        newData.shift();
        max = Math.max(max, data.val);
        min = Math.min(min, data.val);
        let normalized = ((data.val - min) / (max - min)) * 100;
        console.log(data.val);
        newData.push(data.val);
        return {
          ...d,
          datasets: d.datasets.map((set) => {
            return {
              ...set,
              data: newData,
            };
          }),
        };
      });
    };
    return () => {
      socket.send(JSON.stringify({ cmd: "stop" }));
    };
  }, []);

  return <div className="w-1/2">{data.datasets && <Line ref={chartRef} options={options} data={update} redraw={true} />}</div>;
}
