using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Production_planing_web.Controllers
{
    public class ApiController : Controller
    {
        // GET: ApiController
        public ActionResult Index()
        {
            return View();
        }

        public ActionResult Model()
        {
            return View();
        }

        public ActionResult About()
        {
            return View();
        }

        public void Login()
        {

        }

    }
}
