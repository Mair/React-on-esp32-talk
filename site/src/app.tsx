import { Link, Route } from "wouter";
import { Magnetometer } from "./views/Magnetometer";
import { HelloWorld } from "./views/hello-world";
import { PushButton } from "./views/button-push";
import { Servo } from "./views/servo";
import { Led } from "./views/led";

export const App = () => (
  <div>
    <div class="drawer drawer-mobile">
      <input id="my-drawer-2" type="checkbox" class="drawer-toggle" />
      <div class="drawer-content flex flex-col items-center justify-center">
        {/* <!-- Page content here --> */}

        <Route path="/">
          <HelloWorld />
        </Route>
        <Route path="/btn-push">
          <PushButton />
        </Route>
        <Route path="/led" component={Led} />
        <Route path="/magnetometer" component={Magnetometer} />
        <Route path="/servo" component={Servo} />

        <label for="my-drawer-2" class="btn btn-primary drawer-button lg:hidden">
          Open drawer
        </label>
      </div>
      <div class="drawer-side">
        <label for="my-drawer-2" class="drawer-overlay"></label>
        <ul class="menu p-4 overflow-y-auto w-60 md:w-80 bg-base-100 text-base-content">
          {/* <!-- Sidebar content here --> */}
          <Link href="/">
            <li>
              <a>Home</a>
            </li>
          </Link>
          <Link href="/led">
            <li>
              <a>LED</a>
            </li>
          </Link>
          <Link href="/btn-push">
            <li>
              <a>Button push</a>
            </li>
          </Link>
          <Link href="/magnetometer">
            <li>
              <a>magnetometer</a>
            </li>
          </Link>
          <Link href="/servo">
            <li>
              <a>Servo</a>
            </li>
          </Link>
        </ul>
      </div>
    </div>
  </div>
);

const InboxPage = () => <div>inbox</div>;
