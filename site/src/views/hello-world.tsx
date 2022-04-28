import { useEffect, useState } from "preact/hooks";
import Spinner from "../components/spinner";

export const HelloWorld = () => {
  const [message, setMessage] = useState("");

  useEffect(() => {
    fetch("/api/hello-world")
      .then((res) => res.text())
      .then((res) => setMessage(res))
      .catch((err) => console.error(err));
  }, []);

  return (
    <>
      {!message ? (
        <Spinner />
      ) : (
        <div class="alert alert-success shadow-lg text-2xl ">
          <div>
            <svg xmlns="http://www.w3.org/2000/svg" class="stroke-current flex-shrink-0 h-6 w-6" fill="none" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 12l2 2 4-4m6 2a9 9 0 11-18 0 9 9 0 0118 0z" />
            </svg>

            <span>
              ESP32 returned: <strong>{message}!!!</strong>
            </span>
          </div>
        </div>
      )}
    </>
  );
};
